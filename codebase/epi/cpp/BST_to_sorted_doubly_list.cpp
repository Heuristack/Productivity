// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <limits>
#include <memory>

#include "./BST_prototype_shared_ptr.h"

using std::cout;
using std::endl;
using std::make_shared;
using std::numeric_limits;
using std::pair;
using std::shared_ptr;

pair<shared_ptr<BSTNode<int>>, shared_ptr<BSTNode<int>>> BSTToDoublyListHelper(
    const shared_ptr<BSTNode<int>>& T);

// @include
shared_ptr<BSTNode<int>> BSTToDoublyList(
    const shared_ptr<BSTNode<int>>& T) {
  auto res = BSTToDoublyListHelper(T);
  res.second->right = nullptr;  // Breaks the link from tail to head.
  res.first->left = nullptr;  // Breaks the link from head to tail.
  return res.first;
}

// Transforms a BST into a circular sorted circular doubly linked list
// in-place, and return the head of the list.
pair<shared_ptr<BSTNode<int>>, shared_ptr<BSTNode<int>>> 
    BSTToDoublyListHelper(const shared_ptr<BSTNode<int>>& T) {
  // Empty subtree.
  if (!T) {
    return {nullptr, nullptr};
  }

  // Recursively builds the list from left and right subtrees.
  auto left = BSTToDoublyListHelper(T->left);
  auto right = BSTToDoublyListHelper(T->right);

  // Appends T to the list from left subtree.
  T->left = left.second;
  if (left.second) {
    left.second->right = T;
  }

  // Appends the list from right subtree to T.
  T->right = right.first;
  if (right.first) {
    right.first->left = T;
  }

  return {left.first ? left.first : T, right.second ? right.second : T};
}
// @exclude

int main(int argc, char* argv[]) {
  //    3
  //  2   5
  // 1   4 6
  auto root = make_shared<BSTNode<int>>(BSTNode<int>{3});
  root->left = make_shared<BSTNode<int>>(BSTNode<int>{2});
  root->left->left = make_shared<BSTNode<int>>(BSTNode<int>{1});
  root->right = make_shared<BSTNode<int>>(BSTNode<int>{5});
  root->right->left = make_shared<BSTNode<int>>(BSTNode<int>{4});
  root->right->right = make_shared<BSTNode<int>>(BSTNode<int>{6});
  shared_ptr<BSTNode<int>> L = BSTToDoublyList(root);
  shared_ptr<BSTNode<int>> curr = L;
  int pre = numeric_limits<int>::min();
  do {
    assert(pre <= curr->data);
    cout << curr->data << endl;
    pre = curr->data;
    curr = curr->right;
  } while (curr);
  return 0;
}
