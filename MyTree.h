// author : keke
// date : 2023/01/27
#pragma once

#include <vector>
#ifndef __MYTREE__
#define __MYTREE__
#include <BinaryTree.hpp>
#include <some_func.h>
#include <stack>
using std::stack;
using std::vector;
struct MyTree : BinaryTree<int> {

  MyTree(const MyTree &) = default;
  MyTree(MyTree &&) = default;
  MyTree &operator=(const MyTree &) = default;
  MyTree &operator=(MyTree &&) = default;
  virtual void create_tree() override {
    vector<int> data = get_vector_norepeat(16);
    head = new Node_(data[0]);
    std::queue<NodePtr> qe;
    qe.push(head);
    size_t i = 1;
    while (true) {
      if (i == data.size())
        break;
      NodePtr temp = qe.front();
      temp->left = new Node_(data[i++]);
      if (i == data.size())
        break;
      temp->right = new Node_(data[i++]);
      qe.pop();
    }
  }

  queue<NodePtr> foreach_front() const override {
    stack<NodePtr> sk;
    NodePtr temp = head;
    queue<NodePtr> re;
    sk.push(head);
    while (!sk.empty() || temp != nullptr) {
      while (temp != nullptr) {
        re.push(temp); //相当于printf
        sk.push(temp);
        temp = temp->left;
      }
      if (!sk.empty()) {
        temp = sk.top();
        sk.pop(); // 去掉中间节点
        temp = temp->right;
      }
    }
    return re;
  }
  queue<NodePtr> foreach_back() const override {}
  NodePtr insert_node(const int &_val, NodePtr base, Direction dirc) override {
    if (empty()) {
      head = new Node_(_val);
      return head;
    }
  }
  bool find_node(NodePtr ptr) const {
    if (ptr == nullptr)
      return false;
  }
  vector<NodePtr> find_node(const int &_val) const override {
    vector<NodePtr> re;
    //不知道这儿右值引用有没有意义？？？
    auto && order = foreach_front();
    
    
    // 前序遍历
    stack<NodePtr> sk;
    NodePtr temp = head;
    vector<NodePtr> re;
    sk.push(head);
    while (!sk.empty() || temp != nullptr) {
      while (temp != nullptr) {
        if (temp->val == _val)
          re.push_back(temp);
        sk.push(temp);
        temp = temp->left;
      }
      if (!sk.empty()) {
        temp = sk.top();
        sk.pop(); // 去掉中间节点
        temp = temp->right;
      }
    }
    return re;
  }

  bool empty() const override { return head == nullptr; }
};

#endif