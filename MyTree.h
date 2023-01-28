// author : keke
// date : 2023/01/27
#pragma once

#include <vector>
#ifndef __MYTREE__
#define __MYTREE__
#include <BinaryTree.hpp>
#include <functional>
#include <some_func.h>
#include <stack>

using std::queue;
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
    queue<NodePtr> qe;
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
  void copy_tree(const BinaryTree<int> &other) override {
    if(head==other.head) return;
    delete head;
    //前序遍历复制
    std::function<void(NodePtr, NodePtr &)> func = [&](NodePtr _head,
                                                       NodePtr &me) {
      if (_head == nullptr)
       return;
      me = new Node_(*_head);
      func(_head->left, me->left);
      func(_head->right, me->left); 
    };
    func(other.head, head);

    //后续遍历复制
  }
  vector<NodePtr> foreach_front() const override {
    stack<NodePtr> sk;
    NodePtr temp = head;
    vector<NodePtr> re;
    while (!sk.empty() || temp != nullptr) {
      while (temp != nullptr) {
        re.push_back(temp); // 相当于printf
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
  vector<NodePtr> foreach_back() const override { return {};}
  NodePtr insert_node(const int &_val, NodePtr base, Direction dirc) override {
    if (empty()) {
      head = new Node_(_val);
      return head;
    }
    if (base == nullptr || !find_node(base))
      return nullptr;
    NodePtr child = nullptr;
    if (dirc == Direction::left) {
      child = base->left;
      base->left = new Node_(_val);
      base->left->left = child;
      child = base->left;
    } else {
      child = base->right;
      base->right = new Node_(_val);
      base->right->left = child;
      child = base->right;
    }
    return child;
  }
  bool find_node(NodePtr ptr) const {
    if (ptr == nullptr)
      return false;
    auto order = foreach_front();
    for (auto item : order) {
      if (item == ptr)
        return true;
    }

    return false;
  }
  vector<NodePtr> find_node(const int &_val) const override {
    vector<NodePtr> re;
    // NRVO order和函数中re是同一变量
    auto order = foreach_front();
    for (auto item : order) {
      if (item->val == _val)
        re.push_back(item);
    }
    return re;
  }

  bool empty() const override { return head == nullptr; }
};

#endif