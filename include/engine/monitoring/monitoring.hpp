#pragma once
#include <chrono>
#include <thread>
#include <type_traits>
#include <functional>
#include <fstream>

#include "./concepts.hpp"

namespace ngn
{
template<TimePoint T>
struct Interval;

using SystemTimePoint = std::chrono::time_point<std::chrono::system_clock>;

using SystemDuration = SystemTimePoint::duration;

using SystemInterval = Interval<SystemTimePoint>;

std::ifstream open_ifstream_procstat(pid_t pid, pid_t tid = 0);

struct ProcStatData
{
    int pid; 
	char name[16];
    char state;
	int ppid;
	int pgrp;
	int session;
	int tty_nr;
	int tpgid;
	unsigned int flags;
	long unsigned int minflt;
	long unsigned int cminflt;
	long unsigned int majflt;
	long unsigned int cmajflt;
	long unsigned int utime;
	long unsigned int stime;
	long int cutime;
	long int cstime;
	long int priority;
	long int nice;
	long int num_threads;
	long int itrealvalue;
	long long unsigned int starttime;
    long unsigned int vsize;
    long int rss;
    long unsigned int rsslim;
    long unsigned int startcode;
	long unsigned int endcode;
	long unsigned int startstack;
	long unsigned int kstkesp;
    long unsigned int kstkeip;
	long unsigned int signal;
	long unsigned int blocked;
    long unsigned int sigignore;
	long unsigned int sigcatch;
	long unsigned int wchan;
	long unsigned int nswap;
	long unsigned int cnswap;
	int exit_signal;
    int processor;
	unsigned int rt_priority;
    unsigned int policy;	
    long long unsigned int delayacct_blkio_ticks;
    long unsigned int guest_time;
	long unsigned int cguest_time;
	long unsigned int start_data;
	long unsigned int end_data;
    long unsigned int start_brk; 
	long unsigned int arg_start;
	long unsigned int arg_end;
	long unsigned int env_start;
	long unsigned int env_end;
	int exit_code;
};

ProcStatData parsing_procstat(std::istream& in);

template<TimePoint T>
struct Interval
{
  T start;
  T stop;
};

template<TimePoint T>
constexpr T start(const Interval<T>& i)
{
    return i.start;
}

template<TimePoint T>
constexpr T stop(const Interval<T>& i)
{
    return i.stop;
}

template<TimePoint T>
constexpr T start(const std::pair<T, T>& i)
{
    return i.first;
}

template<TimePoint T>
constexpr T stop(const std::pair<T, T>& i)
{
    return i.second;
}

template<TimePoint T>
constexpr auto duration(const T& start, const T& end)
{
  return end - start;
}

template<TimePoint T, typename Callable>
constexpr auto get_task_interval(Callable&& task1)
{
    return [task1 = std::move(task1)](){
        auto start = T::clock::now();
        if constexpr(std::is_same_v<void, std::invoke_result_t<Callable>>)
        {
          task1();
          auto end = T::clock::now();
          return std::make_pair(start, end);
        }
        else
        {
          auto res = task1();
          auto end = T::clock::now();
          return std::tuple_cat(std::make_pair(start, end), std::move(res));
        }
    };
}


} // namespace ngn
