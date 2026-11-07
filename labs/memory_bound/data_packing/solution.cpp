#include "solution.h"
#include <algorithm>
#include <array>
#include <random>

void solution(std::vector<S> &arr) {
  // 1. shuffle - this operation is bound by two things:
  // the speed of the random number generator and the size of the structure
  static std::random_device rd;
  static std::mt19937 g(rd());
  std::shuffle(arr.begin(), arr.end(), g);

  // 2. counting sort
  constexpr int cntSize = maxRandom - minRandom + 1;
  std::array<int, cntSize> cnt{};
  // memory bound operation as well, iterating over array
  for (const auto& v : arr) {
    ++cnt[v.i - minRandom + 1];
  }
  for (int i = 1; i < cntSize; ++i) {
    cnt[i] += cnt[i - 1];
  }
  // 1M elements - memory bound operation again
  std::vector<S> sorted(N);
  for (const auto& v : arr) {
    sorted[cnt[v.i - minRandom]++] = v;
  }
  arr = sorted;
}
