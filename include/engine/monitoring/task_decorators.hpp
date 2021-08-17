#pragma once
#include <tuple>
#include <type_traits>
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
 * @snippet monitoring/task_decorator-test.cpp task_native_handle_ex1
 * @ingroup Monitoring
 */
template<typename Callable>
constexpr auto link(Callable&& f, ThreadNativeHandle& handle);

/**
 * @brief decorate - decorate the task by adding timer between the task and returning the measured interval
 * @return a callable that a return a tuple with a time interval and the callable return type
 * @snippet monitoring/task_decorator-test.cpp task_time_interval_ex2
 * @ingroup Monitoring
 */
template<TimePointInterval interval, typename callable>
auto decorate(callable&& task1);

/**
 * @brief decorate - decorate the task by adding timer between the task and returning the measured interval
 * @return a callable that a return a tuple with a time interval and the callable return type
 * @snippet monitoring/task_decorator-test.cpp task_time_interval_ex3
 * @ingroup Monitoring
 */
template<Clock interval, typename callable>
auto decorate(callable&& task1);

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

template<TimePointInterval Interval, typename Callable>
requires (!std::is_same_v<void, std::invoke_result_t<Callable>>)
auto decorate(Callable&& task1)
{
    return [&](){
        Interval interval;
        start(interval) = Interval::time_point::clock::now();
        auto res = task1();
        end(interval) = Interval::time_point::clock::now();
        return std::tuple_cat(interval, std::move(res));
    };
}

template<TimePointInterval Interval, typename Callable>
requires std::is_same_v<void, std::invoke_result_t<Callable>>
auto decorate(Callable&& task1)
{
    return [&](){
        Interval interval;
        start(interval) = Interval::time_point::clock::now();
        task1();
        end(interval) = Interval::time_point::clock::now();
        return interval;
    };
}

template<Clock clock, typename Callable>
auto decorate(Callable&& task1)
{
   return decorate<TimeInterval<typename clock::time_point>>(task1);
}


}
