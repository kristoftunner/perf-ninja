#include <vector>

// Assume those constants never change
constexpr int N = 1000000;
constexpr int minRandom = 0;
constexpr int maxRandom = 100;

// FIXME: this data structure can be reduced in size
struct S {
  int i; // offset:0, size:4 padding:0
  long long l; // offset: 8, size: 8, padding: 4
  short s; // offset: 16, size: 2, padding: 0
  double d; // offset: 24, size: 8, padding: 6
  bool b; // offset 32, size: 1, padding: 0
  // padding: 7 bytes for the 8 byte alignment

  bool operator<(const S &s) const { return this->i < s.i; }
}; // size: 40, alignment: 8

struct S_start {
  long long l; // offset: 0, size: 8, padding: 0
  double d; // offset: 8, size: 8, padding: 0
  int i; // offset:16, size:4 padding:0
  short s; // offset: 20, size: 2, padding: 0
  bool b; // offset 22, size: 1, padding: 0
  // padding: 1 bytes for the 8 byte alignment
  bool operator<(const S &s) const { return this->i < s.i; }
}; // size: 24, alignment: 8

void init(std::vector<S> &arr);
S create_entry(int first_value, int second_value);
void solution(std::vector<S> &arr);
