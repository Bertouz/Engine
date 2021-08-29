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

  initscr();
  cbreak();
  curs_set(0);
  int ymax, xmax;
  getmaxyx(stdscr, ymax, xmax);
  WINDOW* info_win = newwin(4, xmax-2, 1, 1);
  mvwprintw(info_win, 1, 1, "pid %s", "myname");
  box(info_win, 0, 0);
  int c = wgetch(info_win);
  endwin();

  auto run_parsing = [&istat, &stats,&stats_mutex, &stats_cv, &ok, &pause_duration]()
  {
    while (ok)
    {
      auto start = std::chrono::steady_clock::now();

	  auto lock = std::unique_lock(stats_mutex);

      stats.push(ngn::parsing_procstat(istat));

	  stats_cv.notify_one();

      istat.clear();

      istat.seekg(0);

	  auto end = std::chrono::steady_clock::now();

	  auto d = pause_duration - std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	  std::cout<<"pause : "<<d.count()<<std::endl;

      std::this_thread::sleep_for(d);

    }
  };

  std::thread producer_thread(run_parsing);

  producer_thread.join();

  return 0;
}

      //const long int fs = sysconf(_SC_CLK_TCK);
	  
      //double total_time = 1000 * double(stat.utime + stat.stime + stat.cutime + stat.cstime) / fs;

      //axis.push_back(curr_time);

      //dt.push_back(total_time - prev_time);
	  
      //prev_time = total_time;

      //curr_time += pause_duration.count();
