#pragma once
#include <chrono>
#include <thread>
#include <type_traits>
#include <functional>

#include "./concepts.hpp"

namespace ngn
{
template<TimePoint T>
struct Interval;

using SystemTimePoint = std::chrono::time_point<std::chrono::system_clock>;

using SystemDuration = SystemTimePoint::duration;

using SystemInterval = Interval<SystemTimePoint>;

std::thread::native_handle_type get_native_handle_value();

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

template<typename Callable, typename Callable2>
constexpr auto chain_task(Callable&& task1, Callable2&& task2)
{
    return [task1 = std::move(task1), task2 = std::move(task2)](){
        if constexpr(std::is_same_v<void, std::invoke_result_t<Callable>> && std::is_same_v<void, std::invoke_result_t<Callable2>>)
        {
          task1();
          task2();
          return;
        }
        else if constexpr(!std::is_same_v<void, std::invoke_result_t<Callable>> && std::is_same_v<void, std::invoke_result_t<Callable2>>)
        {
          auto res = task1();
          task2();
          return res;
        }
        else if constexpr(std::is_same_v<void, std::invoke_result_t<Callable>> && !std::is_same_v<void, std::invoke_result_t<Callable2>>)
        {
          task1();
          auto res = task2();
          return res;
        }
        else
        {
          auto res1 = task1();
          auto res2 = task2();
          return std::tuple_cat(res1, res2);
        }
    };
}

} // namespace ngn
