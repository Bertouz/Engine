#include <benchmark/benchmark.h>

extern "C" void fftw3_wrapper_r2r(benchmark::State& pState);

BENCHMARK(fftw3_wrapper_r2r);
