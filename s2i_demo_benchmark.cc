#include <benchmark/benchmark.h>
#include <cassert>
#include <cstdint>
#include <random>
#include <string>

#include "s2i_demo.h"

class MyFixture : public benchmark::Fixture {
 public:
  static char* num_str_tbl;
  static const size_t tbl_str_n{10};
  static const size_t str_size{16};
  int ground_truth[tbl_str_n];
  std::mt19937 rd;
  std::uniform_int_distribution<int> dist;
  bool initialized;

  MyFixture() : rd{std::random_device{}()}, dist{INT32_MIN, INT32_MAX} {
    num_str_tbl = new char[tbl_str_n * str_size];
    assert(num_str_tbl);
    for (int i = 0; i < tbl_str_n; ++i) {
      ground_truth[i] = dist(rd);
      sprintf(num_str_tbl + i * str_size, "%d\0", ground_truth[i]);
    }
  }
  ~MyFixture() { delete[] num_str_tbl; }
};

// non-const static member must be initialized outside class definition
char* MyFixture::num_str_tbl{nullptr};

BENCHMARK_F(MyFixture, benchmark_my_s2i)(benchmark::State& state) {
  for (auto _ : state) {
    for (size_t i = 0; i < MyFixture::tbl_str_n; ++i) {
      benchmark::DoNotOptimize(
          str2int(MyFixture::num_str_tbl + i * MyFixture::str_size));
    }
  }
}

BENCHMARK_F(MyFixture, benchmark_builtin_stoi)(benchmark::State& state) {
  for (auto _ : state) {
    for (size_t i = 0; i < MyFixture::tbl_str_n; ++i) {
      benchmark::DoNotOptimize(
          std::stoi(MyFixture::num_str_tbl + i * MyFixture::str_size));
    }
  }
}

BENCHMARK_MAIN();
