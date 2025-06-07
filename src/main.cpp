// Copyright 2022 NNTU-CS
#include "tree.h"
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
int main() {
  std::vector<char> example = {'1', '2', '3'};
  PMTree tree(example);

  auto perms = getAllPerms(tree);
  for (const auto& p : perms) {
    for (char c : p) std::cout << c;
  }

  auto v1 = getPerm1(tree, 1);
  for (auto c : v1) std::cout << c;

  auto v2 = getPerm2(tree, 2);
  for (auto c : v2) std::cout << c;

  for (int n = 3; n <= 8; ++n) {
    std::vector<char> alpha;
    for (int i = 0; i < n; ++i) alpha.push_back('a' + i);
    PMTree t(alpha);

    std::mt19937 gen(2024 + n);
    std::uniform_int_distribution<> dist(1, static_cast<int>(factorial(n)));
    int idx = dist(gen);

    auto t0 = std::chrono::high_resolution_clock::now();
    getAllPerms(t);
    auto t1 = std::chrono::high_resolution_clock::now();
    getPerm1(t, idx);
    auto t2 = std::chrono::high_resolution_clock::now();
    getPerm2(t, idx);
    auto t3 = std::chrono::high_resolution_clock::now();

    double dt_all = std::chrono::duration<double>(t1 - t0).count();
    double dt_1 = std::chrono::duration<double>(t2 - t1).count();
    double dt_2 = std::chrono::duration<double>(t3 - t2).count();

    std::cout << "n = " << n << "getAllPerms " << dt_all << " сек "
              << "getPerm1 " << dt_1 << " сек "
              << "getPerm2 " << dt_2 << " сек";
  }

  return 0;
}
