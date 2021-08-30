#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#include <chrono>
#include <condition_variable>
#include <iterator>
#include <thread>
#include <vector>
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <future>

#include "CLI/CLI.hpp"
#include "engine/plot.hpp"
#include "engine/monitoring/monitoring.hpp"
#include <ncurses.h>

using namespace std::chrono_literals;

int main(int argc, char** argv)
{
  CLI::App app("A tool to watch and plot the active time of a process at fixed intervals");

  int interval;

  bool ok = true;
  
  std::vector<double> dt;
  
  std::vector<int> axis;

  dt.reserve(100'000);

  axis.reserve(100'000);
  
  pid_t pid = 0;
  
  pid_t tid = 0;

  app.add_option("-i, --interval", interval, "time interval in millisecondes between two samples")->default_val(100);

  app.add_option("pid", pid, "process id of the process we want to watch")->required();

  app.add_option("tid", tid, "task id of the process identified by [pid] we want to watch");

  app.validate_positionals();

  CLI11_PARSE(app, argc, argv);

  tid = tid == 0 ? pid : tid;

  std::chrono::milliseconds pause_duration(interval);

  std::cout << "Watching process : " << pid << std::endl;

  std::cout << "Watching task : " << tid << std::endl;

  std::ifstream istat = ngn::open_ifstream_procstat(pid, tid);

  std::queue<ngn::ProcStatData> stats;
  std::mutex stats_mutex;
  std::condition_variable stats_cv;

  auto run_parsing = [&istat, &stats,&stats_mutex, &stats_cv, &ok, &pause_duration]()
  {
    while (ok)
    {
      auto start = std::chrono::steady_clock::now();

	  auto lock = std::unique_lock(stats_mutex);

      stats.push(ngn::parsing_procstat(istat));

	  stats_cv.notify_one();

	  lock.unlock();

      istat.clear();

      istat.seekg(0);

	  auto end = std::chrono::steady_clock::now();

	  auto d = pause_duration - std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

      std::this_thread::sleep_for(d);

    }
  };

  std::thread producer_thread(run_parsing);
  std::this_thread::sleep_for(pause_duration);

  initscr();
  cbreak();
  curs_set(0);
  int ymax, xmax;
  getmaxyx(stdscr, ymax, xmax);
  WINDOW* info_win = newwin(4, xmax-2, 1, 1);
  int plot_win_width = xmax-2;
  int plot_win_height = ymax - 6;
  WINDOW* plot_win = newwin(plot_win_height, plot_win_width, 1+4, 1);
  box(info_win, 0, 0);
  box(plot_win, 0, 0);
  std::vector<int> plot_data(plot_win_width - 2, 0);
  const long int fs = sysconf(_SC_CLK_TCK);
  ngn::ProcStatData first = stats.front();
  int previous_utime = first.utime;
  while(ok)
  {
      while(!stats.empty())
      {
        ngn::ProcStatData stat = stats.front();

        std::unique_lock<std::mutex> lock(stats_mutex);
        stats.pop();
        lock.unlock();

		mvwaddch(info_win, 1, xmax/4+8,stat.state);

		// writing pid
		int info_win_x_offset = 1;
		std::string pid_label = "pid: " + std::to_string(stat.pid);
		mvwaddstr(info_win, 1, info_win_x_offset, pid_label.c_str());
		// writing exe name
		info_win_x_offset += pid_label.size() + 1;
		std::string name_label = "name: " + std::string(stat.name);
		mvwaddstr(info_win, 1, info_win_x_offset, name_label.c_str());

		// writing state 
		info_win_x_offset += name_label.size() + 1;
		std::string state_label = "state: " + std::string(1, stat.state);
		mvwaddstr(info_win, 1, info_win_x_offset, state_label.c_str());
		// writing num threads
		info_win_x_offset += state_label.size() + 1;
		std::string num_threads_label = "number of threads: " + std::to_string(stat.num_threads);
		mvwaddstr(info_win, 1, info_win_x_offset, num_threads_label.c_str());

		// writing cpu
		info_win_x_offset += num_threads_label.size() + 1;
		std::string cpu_label = "cpu: " + std::to_string(stat.processor);
		mvwaddstr(info_win, 1, info_win_x_offset, cpu_label.c_str());

		// writing utime 
		info_win_x_offset += cpu_label.size() + 1;
		std::string time_label = "time: " + std::to_string(stat.utime + stat.stime);
		mvwaddstr(info_win, 1, info_win_x_offset, time_label.c_str());

		// writing utime 
		info_win_x_offset += time_label.size() + 1;
		std::string debug_label = "active percent: " + std::to_string(100 * 10 * (stat.utime - previous_utime)/(float)interval);
		mvwaddstr(info_win, 1, info_win_x_offset, debug_label.c_str());

		int nb_ybin = plot_win_height - 3;

		// Clear previous plot
		for(int id = 0; id < plot_data.size(); ++id)
		{
           mvwaddch(plot_win, 1 + nb_ybin - plot_data[id], id + 1, ' ');
		}

		// move data to the left so that we only modify the last value
		std::rotate(plot_data.begin(), plot_data.begin()+1, plot_data.end());

		// update last value
		plot_data[plot_data.size()-1] = 10*(stat.utime - previous_utime)*nb_ybin/interval;

		// set the previous to current so that we can compute the variation
		previous_utime = stat.utime;

		// plot the data
		for(int id = 0; id < plot_data.size(); ++id)
		{
           mvwaddch(plot_win, nb_ybin + 1 - plot_data[id], id + 1, '+');
		}

        // refresh the windows so that it show the data
        wrefresh(info_win);
        wrefresh(plot_win);
	  }
	  auto tmp = std::unique_lock(stats_mutex);
	  stats_cv.wait(tmp, [&stats](){return !stats.empty();});
  }
  endwin();

  producer_thread.join();

  return 0;
}
