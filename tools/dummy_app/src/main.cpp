#include <CLI/CLI.hpp>
#include <pthread.h>
#include <unistd.h>
#include <chrono>
#include <thread>

void dummy_run1(std::chrono::milliseconds time, int init, int& res);

void dummy_run2(int init, int& res);

int main(int argc, char** argv)
{

  CLI::App app("A tool to watch and plot the active time of a process at fixed intervals");

  int interval;
  int work_time;

  app.add_option("-i, --interval", interval, "time interval in millisecondes between two samples")->default_val(500);
  app.add_option("-w, --work-time", work_time, "time duration of a work in millisecondes")->default_val(500);

  std::cout<<"Executing in process id : "<< getpid() <<std::endl;

  std::cout<<"Main thread Id : "<< pthread_self() <<std::endl;

  std::chrono::milliseconds pause_duration(interval);

  std::chrono::milliseconds work_time_duration(work_time);

  auto start = std::chrono::steady_clock::now();

  auto max_duration = std::chrono::seconds(600);

  auto current_duration = std::chrono::steady_clock::now() - start;

  int init = 100;

  int res = 0;

  while(current_duration < max_duration)
  {
      dummy_run1(work_time_duration, init, res);

      std::this_thread::sleep_for(pause_duration);

      current_duration = std::chrono::steady_clock::now() - start;
  }

  app.validate_positionals();

  CLI11_PARSE(app, argc, argv);



    return 0;
}

void dummy_run1(std::chrono::milliseconds time, int init, int& res)
{
  auto start = std::chrono::steady_clock::now();

  auto current_duration = std::chrono::steady_clock::now() - start;

  while(current_duration < time)
  {
    res += init * init + init;

    current_duration = std::chrono::steady_clock::now() - start;
  }
}
