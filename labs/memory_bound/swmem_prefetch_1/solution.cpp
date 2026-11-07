#include "solution.hpp"
#include <cstddef>

static int getSumOfDigits(int n) {
  int sum = 0;
  while (n != 0) {
    sum = sum + n % 10;
    n = n / 10;
  }
  return sum;
}

int solution(const hash_map_t *hash_map, const std::vector<int> &lookups) {
  int result = 0;

  const size_t num_of_lookups{lookups.size()};
  for (int i{0}; i < num_of_lookups; i++) {
    const int val{lookups[i]};
    if(i + 1 <= num_of_lookups - 1){
      hash_map->prefetch(lookups[i + 1]);
    }
    if (hash_map->find(val))
      result += getSumOfDigits(val);
  }

  return result;
}

int solution_old(const hash_map_t *hash_map, const std::vector<int> &lookups) {
  int result = 0;

  for (int val : lookups) {
    if (hash_map->find(val))
      result += getSumOfDigits(val);
  }

  return result;
}
