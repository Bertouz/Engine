#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <chrono>
#include <iostream>
#include <vector>

#include "engine/monitoring/monitoring_data.hpp"

TEST_CASE("To push an interval to a container", "[notifier][monitoring]")
{
  ///! notifier_v1
  // std::vector<ngn::TimeIntervalSystem> historic;
  // ngn::TimeIntervalSystem interval;
  // interval.start = std::chrono::system_clock::now();
  // interval.end = std::chrono::system_clock::now();
  // ngn::notify(historic, interval);
  // CHECK(historic.size() == 1);
  // CHECK(historic[0].start == interval.start);
  // CHECK(historic[0].end == interval.end);
  ///! notifier_v1
}
