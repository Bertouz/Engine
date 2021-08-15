#include "engine/monitoring/task_decorators.hpp"
#include "engine/monitoring/monitoring_data.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include <chrono>
#include <iostream>

TEST_CASE("We want to have the start/end time points of a callable","[task_decorator][monitoring]")
{

    ///! [task_time_interval_ex1]
    auto interval = ngn::make_interval<std::chrono::system_clock>();

    auto duration = ngn::duration(interval);

    CHECK(duration.count() == 0);

    int result = 0;

    auto task1 = [&](){
       for(size_t id = 0; id < 1000; ++id)
       {
          result += id*id + 2*id;
       }
    };

    auto monitored_task = ngn::make_decorated_task(task1, interval);

    monitored_task();

    duration = ngn::duration(interval);

    CHECK(duration.count() > 0 );

    CHECK(result == 333832500);
    ///! [task_time_interval_ex1]
}
