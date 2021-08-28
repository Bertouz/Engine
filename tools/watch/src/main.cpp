#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#include <chrono>
#include <thread>

#include "CLI/CLI.hpp"
#include "engine/plot.hpp"

using namespace std::chrono_literals;

std::ifstream open_ifstream_procstat(pid_t pid, pid_t tid = 0);

void sig_handler(int sig);

// Global variables
// Can remove when using bind for sig_handler
bool ok = true;

std::vector<double> dt;

std::vector<int> axis;

pid_t pid = 0;

pid_t tid = 0;

int main(int argc, char** argv)
{
  CLI::App app("A tool to watch and plot the active time of a process at fixed intervals");

  int interval;

  app.add_option("-i, --interval", interval, "time interval in millisecondes between two samples")->default_val(100);

  app.add_option("pid", pid, "process id of the process we want to watch")->required();

  app.add_option("tid", tid, "task id of the process identified by [pid] we want to watch");

  app.validate_positionals();

  CLI11_PARSE(app, argc, argv);

  tid = tid == 0 ? pid : tid;

  std::chrono::milliseconds pause_duration(interval);

  std::cout << "Watching process : " << pid << std::endl;

  std::cout << "Watching task : " << tid << std::endl;

  std::ifstream istat = open_ifstream_procstat(pid, tid);

  std::array<std::string, 52> data;

  dt.reserve(100'000);

  axis.reserve(100'000);

  signal(SIGINT, sig_handler);

  const long int fs = sysconf(_SC_CLK_TCK);

  std::copy(std::istream_iterator<std::string>(istat), std::istream_iterator<std::string>(), data.begin());

  double utime = std::stod(data[13]);
  double stime = std::stod(data[14]);
  double wutime = std::stod(data[15]);
  double wstime = std::stod(data[16]);
  istat.clear();
  istat.seekg(0);
  double prev_time = 1000 * double(utime + stime + wutime + wstime) / fs;

  int curr_time = 0;

  while (ok)
  {
    std::copy(std::istream_iterator<std::string>(istat), std::istream_iterator<std::string>(), data.begin());

    double utime = std::stod(data[13]);
    double stime = std::stod(data[14]);
    double wutime = std::stod(data[15]);
    double wstime = std::stod(data[16]);
    double total_time = 1000 * double(utime + stime + wutime + wstime) / fs;

    axis.push_back(curr_time);
    dt.push_back(total_time - prev_time);

    istat.clear();
    istat.seekg(0);
    prev_time = total_time;
    curr_time += pause_duration.count();
    std::this_thread::sleep_for(pause_duration);
  }

  return 0;
}

void sig_handler(int sig)
{
  switch (sig)
  {
    case SIGINT:
    {
      std::cout << "Watcher interuption called, plotting historic and exiting..." << std::endl;

      plt::Plot plot_dt;

      plot_dt.palette("set2");

      std::string label = "process :" + std::to_string(pid) + ", task id : " + std::to_string(tid);

      plot_dt.drawCurve(axis, dt).label(label).lineWidth(4);

      plt::Figure figure({{plot_dt}});

      figure.size(749, 749);

      figure.show();

      std::cout << "Plotting done, exiting..." << std::endl;

      exit(0);
    }
    default:
    {
      fprintf(stderr, "wasn't expecting that!\n");
      abort();
    }
  }
}

std::ifstream open_ifstream_procstat(pid_t pid, pid_t tid)
{

  std::filesystem::path statfile = std::filesystem::path("/proc") / std::to_string(pid) /
                                   std::filesystem::path("task") / std::to_string(tid) / std::filesystem::path("stat");

  std::cout << statfile << std::endl;

  if (std::filesystem::exists(statfile))
  {
    return std::ifstream(statfile.string());
  }
  throw std::runtime_error("THe file :" + statfile.string() + " doesnt exists");
}
