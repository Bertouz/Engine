#pragma once
#include <concepts>
#include <chrono>
#include <utility>

namespace ngn {

/**
 * @brief Clock - Is the concept defining what is a clock
 * I was surprised to not find the concept std::Clock
 * @ingroup Monitoring
 */
template <typename T> concept Clock = std::chrono::is_clock_v<T>;

/**
 * @brief TimePoint - concept defining a TimePoint
 * We use the api of std::chrono::time_point
 * @ingroup Monitoring
 */
template <typename T> concept TimePoint = requires{
        typename T::clock;
        typename T::duration;
        typename T::rep;
        typename T::period;
        std::declval<T>().time_since_epoch();
        T::min();
        T::max();
};

/**
 * @brief We define a TimeInterval as a structure with a start and an end parameter
 * @note Maybe changing to a definition with two getters start() and end() would be better, make this change
 * @ingroup Monitoring
 */
template <typename T> concept TimePointInterval = requires(T a){
  {start(a)}->std::convertible_to<typename T::time_point>;
  {end(a)}->std::convertible_to<typename T::time_point>;
};

}
