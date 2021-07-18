#include <benchmark/benchmark.h>
#include <MyCppProject/hello.hpp>
#include <sstream>
#include <string>

// Define a benchmark
static void bench_hello(benchmark::State& pState)
{
		std::ostringstream oss;
		for(auto _ : pState)
		{
				my_cpp_project::greet(oss);
		}
}

// Define a benchmark
static void bench_hello_2(benchmark::State& pState)
{
		std::ostringstream oss;
		std::string str;
		for(auto _ : pState)
		{
				str += "hello world";
		}
		oss<<str;

}

// Register the function as a benchmark
BENCHMARK(bench_hello);
BENCHMARK(bench_hello_2);
