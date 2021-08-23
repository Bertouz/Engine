#pragma once
#include <chrono>
#include <concepts>
#include <utility>

namespace ngn
{

/**
 * @brief Clock - Is the concept defining what is a clock
 * I was surprised to not find the concept std::Clock
 * @ingroup Monitoring
 */
template<typename T>
concept Clock = std::chrono::is_clock_v<T>;

/**
 * @brief TimePoint - concept defining a TimePoint
 * We use the api of std::chrono::time_point
 * @ingroup Monitoring
 */
template<typename T>
concept TimePoint = requires
{
  typename T::clock;
  Clock<typename T::clock>;
  typename T::duration;
  typename T::rep;
  typename T::period;
  std::declval<T>().time_since_epoch();
  T::min();
  T::max();
};

} // namespace ngn
