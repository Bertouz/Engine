
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <chrono>
#include <iostream>

#include "engine/contexts/task_utils.hpp"

TEST_CASE("We to have the native handle of the thread in which a callable is called",
          "[contexts][task_utils][native_handle]")
{

  ///! [task_native_handle_ex1]
  std::thread::native_handle_type handle = 0;

  int result = 0;

  auto task1 = [&]() {
    for (size_t id = 0; id < 1000; ++id)
    {
      result += id * id + 2 * id;
    }
    handle = ngn::get_worker_handle();
  };

  task1();

  // check the value is initialized
  CHECK(handle);

  // check the task is run
  CHECK(result == 333832500);
  ///! [task_native_handle_ex1]
}
