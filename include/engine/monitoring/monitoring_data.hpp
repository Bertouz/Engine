#pragma once
#include <chrono>
#include <thread>
#include "./concepts.hpp"

namespace ngn {

/**
 * @brief TimeInterval
 * @ingroup Monitoring
 */
template<TimePoint T>
struct TimeInterval;

/**
 * @brief ThreadNativeHandle
 * @ingroup Monitoring
 */
struct ThreadNativeHandle;

inline std::thread::native_handle_type get_native_handle_value();
/**
 * @brief make_interval
 * @ingroup Monitoring
 */
template<Clock T>
constexpr auto make_interval();

/**
 * @brief duration
 * @param interval
 * @ingroup Monitoring
 */
template<TimePointInterval T>
constexpr auto duration(const T& interval);

/**
 * @brief start
 * @param interval
 * @ingroup Monitoring
 */
template<TimePoint T>
constexpr auto start(TimeInterval<T>& interval)->T&;

/**
 * @brief start
 * @param interval
 * @ingroup Monitoring
 */
template<TimePoint T>
constexpr auto start(const TimeInterval<T>& interval)->const T&;

/**
 * @brief end
 * @param interval
 * @ingroup Monitoring
 */
template<TimePoint T>
constexpr auto end(TimeInterval<T>& interval)->T&;

/**
 * @brief end
 * @param interval
 * @ingroup Monitoring
 */
template<TimePoint T>
constexpr auto end(const TimeInterval<T>& interval)->const T&;

}

namespace ngn {

template<TimePoint T>
struct TimeInterval
{
    using time_point = T;
    T start;
    T end;
};

template<Clock T>
constexpr auto make_interval()
{
    return TimeInterval<typename T::time_point>{};
}

template<TimePoint T>
constexpr auto start(TimeInterval<T>& interval)->T&
{
    return interval.start;
}

template<TimePoint T>
constexpr auto end(TimeInterval<T>& interval)->T&
{
    return interval.end;
}

template<TimePoint T>
constexpr auto start(const TimeInterval<T>& interval)->const T&
{
    return interval.start;
}

template<TimePoint T>
constexpr auto end(const TimeInterval<T>& interval)->const T&
{
    return interval.end;
}

template<TimePointInterval T>
constexpr auto duration(const T& interval)
{
    return end(interval) - start(interval);
}

struct ThreadNativeHandle
{
    std::thread::native_handle_type value = 0;
};

inline std::thread::native_handle_type get_native_handle_value()
{
#ifdef __linux__
        return pthread_self();
#elif _WIN32
        return GetCurrentThread();
#endif
}


}
