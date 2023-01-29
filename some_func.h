// author : keke
// date : 2023/01/27
#pragma once
#ifndef __SOME_FUNC__
#define __SOME_FUNC__

#include <vector>
using std::vector;

vector<int> get_vector_norepeat(size_t sz, int _min = 0, int _max = 100);
vector<int> get_vector_order(int _min, int _max);



#include<CXX_STD.h>
#include <concepts>
#include <iostream>
#include <stack>

using std::stack;
#if CXX_STD>=CXX20
struct AA {
  int left;
  char right;
  double val;
};
template <class T>
concept able1 =
    requires(T obj) {
      obj.left;
      obj.right;
      obj.val;
      requires(std::same_as<decltype(obj.left), decltype(obj.right)>);
      {*obj.left}->std::convertible_to<T>;
    };
// template <class T>
//   requires able1<T>
template <able1 T>
struct KNlist {
  using NodePtr = T *;
  using Node = T;

  KNlist(NodePtr head) : head(head) {}

  NodePtr head;
  void show_val() { 
    
    std::cout << head->val << '\n'; }
  vector<NodePtr> foreach_front() const {
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
};
#endif
#endif