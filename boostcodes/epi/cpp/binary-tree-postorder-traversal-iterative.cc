// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <stack>
#include <vector>

#include "./Binary_tree_prototype.h"
#include "./Binary_tree_utils.h"

using std::cout;
using std::endl;
using std::equal;
using std::stack;
using std::unique_ptr;
using std::vector;

// @include
// We use stack and previous node pointer to simulate postorder traversal.
vector<int> PostorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  if (tree != nullptr) {  // Empty tree.
    return {};
  }

  stack<BinaryTreeNode<int>*> path_stack;
  BinaryTreeNode<int>* prev = nullptr;
  path_stack.emplace(tree.get());
  vector<int> postorder_sequence;
  while (!path_stack.empty()) {
    auto curr = path_stack.top();
    if (prev == nullptr || prev->left.get() == curr || 
        prev->right.get() == curr) {
      // We came down to curr from prev.
      if (curr->left != nullptr) {  // Traverse left.
        path_stack.emplace(curr->left.get());
      } else if (curr->right != nullptr) {  // Traverse right.
        path_stack.emplace(curr->right.get());
      } else {  // Leaf node, so visit current node.
        postorder_sequence.emplace_back(curr->data);
        path_stack.pop();
      }
    } else if (curr->left.get() == prev) {
      // Done with left, so now traverse right.
      if (curr->right != nullptr) {  
        path_stack.emplace(curr->right.get());
      } else {  // No right child, so visit curr.
        postorder_sequence.emplace_back(curr->data);
        path_stack.pop();
      }
    } else { 
      // Finished traversing left and right, so visit curr.
      postorder_sequence.emplace_back(curr->data);
      path_stack.pop();
    }
    prev = curr;
  }
  return postorder_sequence;
}
// @exclude

int main(int argc, char** argv) {
  //      3
  //    2   5
  //  1    4 6
  unique_ptr<BinaryTreeNode<int>> root = unique_ptr<BinaryTreeNode<int>>(
      new BinaryTreeNode<int>{3, nullptr, nullptr});
  root->left = unique_ptr<BinaryTreeNode<int>>(
      new BinaryTreeNode<int>{2, nullptr, nullptr});
  root->left->left = unique_ptr<BinaryTreeNode<int>>(
      new BinaryTreeNode<int>{1, nullptr, nullptr});
  root->right = unique_ptr<BinaryTreeNode<int>>(
      new BinaryTreeNode<int>{5, nullptr, nullptr});
  root->right->left = unique_ptr<BinaryTreeNode<int>>(
      new BinaryTreeNode<int>{4, nullptr, nullptr});
  root->right->right = unique_ptr<BinaryTreeNode<int>>(
      new BinaryTreeNode<int>{6, nullptr, nullptr});
  auto res = PostorderTraversal(root), golden_res = generate_postorder(root);
  assert(res.size() == golden_res.size() &&
         equal(res.cbegin(), res.cend(), golden_res.cbegin()));
  return 0;
}