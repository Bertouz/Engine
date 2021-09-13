#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <regex>
#include <thread>

using namespace std::chrono_literals;

static int cum1 = 0;

static int cum2 = 0;

static bool ok1 = true;

static bool ok2 = true;

void job1()
{
  while (ok1)
  {
    for (int i = 0; i < 500'000; ++i)
      cum2 += 10 * i + 3;
    std::this_thread::sleep_for(100ms);
  }
}

void job2()
{
  while (ok2)
  {
    for (int i = 0; i < 5'000; ++i)
      cum2 += 10 * i + 3;
    std::this_thread::sleep_for(100ms);
  }
}

TEST_CASE("We want to parse the proc stat data of the current process into a defined structure",
          "[parsing][monitoring]")
{
  SECTION("TimeInterval object templated")
  {
    ///! [monitoring_data_parser_v1]
    std::ofstream tmp {"/tmp/torm_torm", std::ios_base::app};

    pid_t pid = getpid();

    std::cout << "pid : " << pid << std::endl;

    const long int fs = sysconf(_SC_CLK_TCK);

    const std::filesystem::path procdir("/proc");

    const std::filesystem::path curr_proc_dir = procdir / std::to_string(pid);

    const std::filesystem::path statfile = curr_proc_dir / std::string("stat");

    std::thread t1(job1);
    std::thread t2(job2);

    for (auto task_dir_entry : std::filesystem::directory_iterator(curr_proc_dir / "task"))
    {
      std::cout << "task : " << task_dir_entry.path() << std::endl;

      std::ifstream ifile((task_dir_entry.path() / "stat").string());

      std::array<std::string, 52> data;

      std::vector<double> time;

      for (int id = 0; id < 20; ++id)
      {
        std::copy(std::istream_iterator<std::string>(ifile), std::istream_iterator<std::string>(), data.begin());

        // std::copy(data.begin(), data.end(), std::ostream_iterator<std::string>(std::cout, " "));
        // std::cout << std::endl;

        double utime = std::stod(data[13]);
        double stime = std::stod(data[14]);
        double wutime = std::stod(data[15]);
        double wstime = std::stod(data[16]);
        double total_time = double(utime + stime + wutime + wstime) / fs;
        std::cout << total_time << " ";
        time.push_back(total_time);
        std::this_thread::sleep_for(500ms);
        ifile.clear();
        ifile.seekg(0);
      }
      std::cout << std::endl;
      std::vector<double> dt(time.size());
      std::adjacent_difference(time.begin(), time.end(), dt.begin());
      std::cout << std::endl;
      std::copy(dt.begin(), dt.end(), std::ostream_iterator<double>(std::cout, " "));
      std::cout << std::endl;

      ///! [monitoring_data_parser_v1]
    }
    ok1 = false;
    t1.join();
    ok2 = false;
    t2.join();
  }
}
