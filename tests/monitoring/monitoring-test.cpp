#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <chrono>
#include <iostream>

#include "engine/monitoring/monitoring.hpp"

TEST_CASE("We want to have the start/end time points of a callable", "[task_decorator][monitoring]")
{
  SECTION("TimeInterval object templated")
  {
    ///! [task_time_interval_ex2]
    int result = 0;

    auto task1 = [&]() {
      for (size_t id = 0; id < 1000; ++id)
      {
        result += id * id + 2 * id;
      }
    };

    auto monitored_task = ngn::get_task_interval<ngn::SystemTimePoint>(task1);

    auto interval = monitored_task();

    auto duration = ngn::duration(ngn::start(interval), ngn::stop(interval));

    CHECK(duration.count() > 0);

    // check the task is run
    CHECK(result == 333832500);
    ///! [task_time_interval_ex2]
  }
}
