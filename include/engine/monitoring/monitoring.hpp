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
