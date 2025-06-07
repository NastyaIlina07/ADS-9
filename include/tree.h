// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_


#include <vector>

class PMTree {
 public:
  struct Node {
    char data;
    std::vector<Node*> next;
    explicit Node(char d) : data(d) {}
  };
  Node* root;
  std::vector<char> base;

  explicit PMTree(const std::vector<char>& vec);
  ~PMTree();

 private:
  Node* createTree(const std::vector<char>& set);
  void clearTree(Node* p);
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int number);
std::vector<char> getPerm2(PMTree& tree, int number);

size_t factorial(int n);

#endif  // INCLUDE_TREE_H_
