// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::stoul;
using std::uniform_int_distribution;
using std::vector;

// @include
int RemoveDuplicates(vector<int>* A) {
  if (A->empty()) {
    return 0;
  }

  auto& A_ref = *A;
  int write_index = 0;
  for (int i = 1; i < A_ref.size(); ++i) {
    if (A_ref[write_index] != A_ref[i]) {
      A_ref[++write_index] = A_ref[i];
    }
  }
  return write_index + 1;
}
// @exclude

void CheckAns(const vector<int> A, size_t n) {
  for (size_t i = 1; i < n; ++i) {
    assert(A[i - 1] != A[i]);
  }
}

int main(int argc, char** argv) {
  default_random_engine gen((random_device())());
  size_t n;
  if (argc == 2) {
    n = stoul(argv[1]);
  } else {
    uniform_int_distribution<size_t> dis_n(0, 10000);
    n = dis_n(gen);
  }
  for (int times = 0; times < 1000; ++times) {
    uniform_int_distribution<int> A_dis(-1000, 1000);
    vector<int> A;
    generate_n(back_inserter(A), n, [&] { return A_dis(gen); });
    sort(A.begin(), A.end());
    auto B(A);
    auto iter = unique(B.begin(), B.end());
    auto size = RemoveDuplicates(&A);
    assert(size == distance(B.begin(), iter));
    CheckAns(A, size);
    cout << size << endl;
  }
  return 0;
}
