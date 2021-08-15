#pragma once
#include "./concepts.hpp"

namespace ngn {

/**
 * @brief make_decorated_task
 * @param f
 * @param interval
 * @snippet monitoring/task_decorator-test.cpp task_time_interval_ex1
 * @ingroup Monitoring
 */
template<typename Callable, TimePointInterval Interval>
constexpr auto make_decorated_task(Callable&& f, Interval& interval)
{
    return [&](){
        start(interval) = Interval::time_point::clock::now();
        f();
        end(interval) = Interval::time_point::clock::now();
    };
}


}
