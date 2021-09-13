#include <CLI/CLI.hpp>
#include <pthread.h>
#include <unistd.h>

#include <algorithm>
#include <chrono>
#include <iterator>
#include <thread>

void dummy_run1(std::chrono::milliseconds pTime, int pInit, int& pRes);

int main(int argc, char** argv)
{

  CLI::App app("A tool to watch and plot the active time of a process at fixed intervals");

  std::vector<int> interval;

  std::vector<int> work_time;

  std::vector<std::string> thread_name;

  app.add_option("-i, --interval", interval, "time interval in millisecondes between two samples, [jal1,val2], where n value will spawn n jobs")->required();

  app.add_option("-w, --work-time", work_time, "time duration of a work in millisecondes, [val1,val2], where n values will spawn n jobs")->required();

  app.add_option(
    "-n, --name",
    thread_name,
    "if you want to give names to your thread you can use this option, it is an array [name1,name2,...namen] where namen is the name of the n-st thread. If the the options is not used each thread will inherit its parent name.");

  std::cout << "Executing in process id : " << getpid() << std::endl;

  std::cout << "Main thread Id : " << pthread_self() << std::endl;

  CLI11_PARSE(app, argc, argv);

  if (interval.size() != work_time.size())
  {
    std::cerr << "The number of intervals and the number of worktime must be the same" << std::endl;
    return -1;
  }

  std::cout<<"printing args : "<<std::endl;
  for(auto i : interval)
		  std::cout<<i<<" ";
  std::cout<<std::endl;
  for(auto i : work_time)
		  std::cout<<i<<" ";
  std::cout<<std::endl;

  std::vector<std::chrono::milliseconds> pause_duration;

  std::transform(interval.begin(), interval.end(), std::back_insert_iterator(pause_duration), [](int i) {
    return std::chrono::milliseconds(i);
  });

  std::vector<std::chrono::milliseconds> work_time_duration;

  std::transform(work_time.begin(),
                 work_time.end(),
                 std::back_insert_iterator(work_time_duration),
                 [](int i) { return std::chrono::milliseconds(i); });

  auto start = std::chrono::steady_clock::now();

  auto max_duration = std::chrono::seconds(600);

  auto current_duration = std::chrono::steady_clock::now() - start;

  std::vector<int> init(interval.size(), 100);

  std::vector<int> res(interval.size(), 0);

  std::vector<std::thread> threads;

  bool ok = current_duration < max_duration;

  auto process = [&](int id) {
    if (!thread_name.empty())
    {
      pthread_setname_np(pthread_self(), thread_name[id].c_str());
    }

    while (ok)
    {
      dummy_run1(work_time_duration[id], init[id], res[id]);

      std::this_thread::sleep_for(pause_duration[id]);

      current_duration = std::chrono::steady_clock::now() - start;
    }
  };

  for (size_t id = 0; id < interval.size(); ++id)
  {
    threads.push_back(std::thread(std::bind(process, id)));
  }

  while (ok)
  {
    ok = current_duration < max_duration;
  }

  for (auto& thread : threads)
  {
    thread.join();
  }

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
