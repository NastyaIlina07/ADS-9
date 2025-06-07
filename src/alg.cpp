// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "tree.h"

#include <algorithm>
#include <vector>


PMTree::PMTree(const std::vector<char>& vec) : base(vec) {
  root = createTree(vec);
}

PMTree::~PMTree() { clearTree(root); }

PMTree::Node* PMTree::createTree(const std::vector<char>& set) {
  if (set.empty()) return nullptr;
  std::vector<char> ordered = set;
  std::sort(ordered.begin(), ordered.end());
  Node* node = new Node(0);
  for (char elem : ordered) {
    std::vector<char> nextSet;
    for (char ch : ordered)
      if (ch != elem) nextSet.push_back(ch);
    Node* child = new Node(elem);
    child->next.clear();
    Node* subtree = createTree(nextSet);
    if (subtree) child->next.push_back(subtree);
    node->next.push_back(child);
  }
  return node;
}

void PMTree::clearTree(Node* p) {
  if (!p) return;
  for (Node* child : p->next) clearTree(child);
  delete p;
}

void collect(Node* node, std::vector<char>& path,
             std::vector<std::vector<char>>& output, int depth, int maxDepth) {
  if (depth == maxDepth) {
    output.push_back(path);
    return;
  }
  for (Node* child : node->next) {
    path.push_back(child->data);
    if (!child->next.empty())
      collect(child->next[0], path, output, depth + 1, maxDepth);
    else
      collect(child, path, output, depth + 1, maxDepth);
    path.pop_back();
  }
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  std::vector<std::vector<char>> result;
  std::vector<char> temp;
  int total = tree.base.size();
  if (tree.root) {
    collect(tree.root, temp, result, 0, total);
  }
  return result;
}

std::vector<char> getPerm1(PMTree& tree, int number) {
  auto all = getAllPerms(tree);
  if (number < 1 || number > static_cast<int>(all.size())) return {};
  return all[number - 1];
}

size_t factorial(int n) {
  size_t result = 1;
  for (int i = 2; i <= n; ++i) result *= i;
  return result;
}

std::vector<char> getPerm2(PMTree& tree, int number) {
  int n = tree.base.size();
  if (number < 1 || number > static_cast<int>(factorial(n))) return {};
  std::vector<char> chars = tree.base;
  std::sort(chars.begin(), chars.end());
  std::vector<char> answer;
  int idx = number - 1;
  std::vector<bool> used(n, false);
  for (int i = n; i > 0; --i) {
    size_t f = factorial(i - 1);
    int q = idx / static_cast<int>(f);
    int cnt = 0, pos = -1;
    for (int j = 0; j < n; ++j) {
      if (!used[j]) {
        if (cnt == q) {
          pos = j;
          break;
        }
        cnt++;
      }
    }
    answer.push_back(chars[pos]);
    used[pos] = true;
    idx %= f;
  }
  return answer;
}
