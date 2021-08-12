#include "engine/algorithms/generation.hpp"
#include "engine/contexts/strand.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include <chrono>

TEST_CASE("We want to give callable to be run sequentially asynchronously in a host context", "[contexts][strand]")
{
    using namespace std::chrono_literals;

    constexpr size_t nb_elements = 20;

    std::vector<double> x(nb_elements, 0);

    ngn::range(x.begin(), x.end(), -10.0, 10.0);

    std::vector<double> x2(nb_elements, 0);

    std::transform(x.begin(), x.end(), x2.begin(), [](auto xv) { return xv * xv; });

    std::vector<double> z(nb_elements, 0);

    auto vector_add = [&x, &x2, &z]() {
        for (size_t id = 0; id < x.size(); ++id)
        {
            z[id] = x[id] + x2[id];
        }
    };

    auto vector_mult_2 = [&z]() {
        for (size_t id = 0; id < z.size(); ++id)
        {
            z[id] = z[id] * 2;
        }
    };

    ngn::Strand context;

    // Add a new task to the queue and start the processing if not already running
    ngn::post(context, vector_add);

    ngn::post(context, vector_mult_2);

    // Request to stop the process when all given tasks are finished
    ngn::wait(context);

    std::vector<double> z_ref{180.0,         142.216066482,  108.864265928,  79.944598338,   55.4570637119,
                              35.4016620499, 19.7783933518,  8.5872576177,   1.8282548476,   -0.4986149584,
                              1.6066481994,  8.1440443213,   19.1135734072,  34.5152354571,  54.3490304709,
                              78.6149584488, 107.3130193906, 140.4432132964, 178.0055401662, 220.0};

    CHECK_THAT(z, Catch::Matchers::Approx(z_ref).epsilon(0.001));
}
