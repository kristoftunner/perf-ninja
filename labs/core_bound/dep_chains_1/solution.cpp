#include "solution.hpp"
#include <array>
#include <iostream>

unsigned getSumOfDigits(unsigned n) {
  unsigned sum = 0;
  while (n != 0) {
    sum = sum + n % 10;
    n = n / 10;
  }
  return sum;
}

// Task: lookup all the values from l2 in l1.
// For every found value, find the sum of its digits.
// Return the sum of all digits in every found number.
// Both lists have no duplicates and elements placed in *random* order.
// Do NOT sort any of the lists. Do NOT store elements in a hash_map/sets.

// Hint: Traversing a linked list is a long data dependency chain:
//       to get the node N+1 you need to retrieve the node N first.
//       Think how you can execute multiple dependency chains in parallel.
unsigned solution_slow(List *l1, List *const l2) {
  unsigned retVal = 0;

  List *head2 = l2;
  // O(N^2) algorithm:
  while (l1) {
    unsigned v = l1->value;
    head2 = l2;
    while (head2) {
      if (head2->value == v) {
        retVal += getSumOfDigits(v);
        break;
      }
      head2 = head2->next;
    }
    l1 = l1->next;
  }

  return retVal;
}

unsigned solution(List *l1, List *const l2) {
  unsigned retVal = 0;

  List *head2 = l2;
  List *head1 = l1;
  constexpr const unsigned int kBatchSize{128U};
  while (head1) {
    // batch l1 into 128 vector
    std::array<unsigned int, 128> batchl1;
    size_t it{0UL};
    while (it < kBatchSize && head1) {
      batchl1[it++] = head1->value;
      head1 = head1->next;
    }
    head2 = l2;
    while (head2) {
      const unsigned int val{head2->value};
      for (int i{0}; i <= it; i++) {
        if (val == batchl1[i]) {
          retVal += getSumOfDigits(batchl1[i]);
          break;
        }
      }
      head2 = head2->next;
    }
  }
  return retVal;
}

unsigned solution_vector(List *l1, List *const l2) {
  unsigned retVal = 0;

  std::vector<unsigned int> l2vector;
  List *head2 = l2;
  while (head2) {
    l2vector.push_back(head2->value);
    head2 = head2->next;
  }
  // O(N^2) algorithm:
  while (l1) {
    unsigned v = l1->value;
    head2 = l2;
    for (const unsigned i : l2vector) {
      if (i == v) {
        retVal += getSumOfDigits(v);
        break;
      }
    }
    l1 = l1->next;
  }

  return retVal;
}
