#pragma once
#include "./concepts.hpp"
#include "./monitoring_data.hpp"

namespace ngn {
/**
 * @brief make_decorated_task
 * @param f
 * @param interval
 * @snippet monitoring/task_decorator-test.cpp task_time_interval_ex1
 * @ingroup Monitoring
 */
template<typename Callable, TimePointInterval Interval>
constexpr auto link(Callable&& f, Interval& interval);

/**
 * @brief make_decorated_task
 * @param f
 * @param interval
 * @snippet monitoring/task_decorator-test.cpp
 * @ingroup Monitoring
 */
template<typename Callable>
constexpr auto link(Callable&& f, ThreadNativeHandle& handle);

}

namespace ngn {

template<typename Callable, TimePointInterval Interval>
constexpr auto link(Callable&& f, Interval& interval)
{
    return [&](){
        start(interval) = Interval::time_point::clock::now();
        f();
        end(interval) = Interval::time_point::clock::now();
    };
}


template<typename Callable>
constexpr auto link(Callable&& f, ThreadNativeHandle& handle)
{
    return [&](){
        handle.value = get_native_handle_value();
        f();
    };
}


}
