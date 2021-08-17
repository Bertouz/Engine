#include "engine/monitoring/task_decorators.hpp"
#include "engine/monitoring/monitoring_data.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include <chrono>
#include <iostream>

TEST_CASE("We want to have the start/end time points of a callable","[task_decorator][monitoring]")
{
    SECTION("link a task to a time interval object for the measured result")
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

      auto monitored_task = ngn::link(task1, interval);

      monitored_task();

      duration = ngn::duration(interval);

      CHECK(duration.count() > 0 );

      CHECK(result == 333832500);
      ///! [task_time_interval_ex1]
    }
    SECTION("TimeInterval object templated")
    {
      ///! [task_time_interval_ex2]
      int result = 0;

      auto task1 = [&](){
         for(size_t id = 0; id < 1000; ++id)
         {
            result += id*id + 2*id;
         }
      };

      auto monitored_task = ngn::decorate<ngn::TimeInterval<std::chrono::system_clock::time_point>>(task1);

      auto interval = monitored_task();

      auto duration = ngn::duration(interval);

      CHECK(duration.count() > 0 );

      CHECK(result == 333832500);
      ///! [task_time_interval_ex2]
    }
    SECTION("Using simple TimeInterval object and just giving the clock")
    {
      ///! [task_time_interval_ex3]
      int result = 0;

      auto task1 = [&](){
         for(size_t id = 0; id < 1000; ++id)
         {
            result += id*id + 2*id;
         }
      };

      auto monitored_task = ngn::decorate<std::chrono::system_clock>(task1);

      auto interval = monitored_task();

      auto duration = ngn::duration(interval);

      CHECK(duration.count() > 0 );

      CHECK(result == 333832500);
      ///! [task_time_interval_ex3]
    }
}

TEST_CASE("We to have the native handle of the thread in which a callable is called","[task_decorator][monitoring][native_handle]")
{

    ///! [task_native_handle_ex1]
    ngn::ThreadNativeHandle handle;

    // check the value is initialized
    CHECK(!handle.value);

    int result = 0;

    auto task1 = [&](){
       for(size_t id = 0; id < 1000; ++id)
       {
          result += id*id + 2*id;
       }
    };

    auto monitored_task = ngn::link(task1, handle);

    monitored_task();

    // check the value is initialized
    CHECK(handle.value);

    // check the task is run
    CHECK(result == 333832500);
    ///! [task_native_handle_ex1]
}

TEST_CASE("We want to decorate a task by adding to the return the time Interval","[task_decorator][monitoring]")
{
}
