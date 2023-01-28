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

template <class T>
concept node_able =
    requires(T obj) {
      obj.left;
      obj.right;
      obj.val;
      requires(std::same_as<decltype(obj.left), decltype(obj.right)>);
      {*obj.left}->std::convertible_to<T>;
    };
template <node_able T = Node<int>> 
struct MyTree : BinaryTree<T> {

  using typename BinaryTree<T>::Node_;
  using typename BinaryTree<T>::NodePtr;
  using typename BinaryTree<T>::Direction;
  using typename BinaryTree<T>::val_type;
  
  NodePtr head;

  
  MyTree() = default;
  MyTree(const MyTree &other) { copy_tree(other); }
  MyTree(MyTree &&) = default;
  MyTree &operator=(const MyTree &) = default;
  MyTree &operator=(MyTree &&) = default;

  virtual void create_tree() override {
    // vector<int> data = get_vector_norepeat(10);
    vector<int> data = get_vector_order(1, 7);

    head = new Node_(data[0]);
    
    queue<NodePtr> qe;
    qe.push(head);
    size_t i = 1;
    while (!qe.empty()) {
      if (i == data.size())
        break;
      NodePtr temp = qe.front();
      temp->left = new Node_(data[i++]);
      qe.push(temp->left);
      if (i == data.size())
        break;
      temp->right = new Node_(data[i++]);
      qe.push(temp->right);
      qe.pop();
    }
  }
  void copy_tree(const BinaryTree<T> &other) override {
    auto _head = other.get_head();
    if (head == _head)
      return;
    delete head;
    // 后序遍历复制
    std::function<NodePtr(NodePtr)> func = [&](NodePtr _head) {
      if (_head == nullptr)
        return _head;
      NodePtr _left = func(_head->left);
      NodePtr _right = func(_head->right);
      NodePtr re = new Node_(_head->val, _left, _right);
      return re;
    };
    head = func(_head);
  }
  virtual NodePtr get_head() const override { return head; }
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
  vector<NodePtr> foreach_mid() const override {
    stack<NodePtr> sk;
    NodePtr temp = head;
    vector<NodePtr> re;
    while (!sk.empty() || temp != nullptr) {
      while (temp != nullptr) {
        sk.push(temp);
        temp = temp->left;
      }
      if (!sk.empty()) {
        temp = sk.top();
        re.push_back(temp); // 相当于printf
        sk.pop();           // 去掉中间节点
        temp = temp->right;
      }
    }
    return re;
  }
  // 后序遍历 如果取出的上一个节点是栈顶的right，就可以取出栈顶
  // 如果不是 就进入右子树
  // 使用双栈
  vector<NodePtr> foreach_back() const override {
    stack<NodePtr> sk;
    NodePtr temp = head;
    NodePtr last = head;
    vector<NodePtr> re;
    while (temp != nullptr || !sk.empty()) {
      while (temp != nullptr) {
        sk.push(temp);
        temp = temp->left;
      }
      temp = sk.top();
      if (temp->right != nullptr) {
        if (temp->right != last) {
          temp = temp->right;
          continue;
        }
      }
      last = temp;
      re.push_back(temp);
      temp = nullptr; // 避免重复访问左子节点
      sk.pop();
    }
    return re;
  }
  vector<NodePtr> foreach_ceng() const override {
    if (empty())
      return {};
    vector<NodePtr> re;
    queue<NodePtr> qe;
    qe.push(head);
    while (!qe.empty()) {
      NodePtr temp = qe.front();
      re.push_back(temp);
      if (temp->left != nullptr)
        qe.push(temp->left);
      if (temp->right != nullptr)
        qe.push(temp->right);
      qe.pop();
    }
    return re;
  }

  bool find_node(NodePtr ptr) const {
    if (ptr == nullptr)
      return false;
    vector<NodePtr> order = foreach_front();
    for (auto item : order) {
      if (item == ptr)
        return true;
    }
    return false;
  }
  vector<NodePtr> find_node(const val_type &_val) const override {
    vector<NodePtr> re;
    // NRVO order和函数中re是同一变量
    vector<NodePtr> order = foreach_front();
    for (auto item : order) {
      if (item->val == _val)
        re.push_back(item);
    }
    return re;
  }
  NodePtr insert_node(const val_type &_val, NodePtr base, Direction dirc) override {
    auto arr = get_leaves();
    if (arr.count(base) > 0) {
      if (base->left == nullptr && dirc == Direction::left) {
        base->left = new Node_(_val);
        return base->left;
      }
      if (base->right == nullptr && dirc == Direction::right) {
        base->right = new Node_(_val);
        return base->right;
      }
    }
    return nullptr;
  }
  size_t delete_node(const val_type &_val) override {
    ;
    return 0;
  }
  // 深度
  size_t depth() const override { return 0; }
  // 反转左右子树
  void reverse_tree() override {}
  std::set<NodePtr> get_leaves() const override {
    std::set<NodePtr> re;
    std::function<void(NodePtr)> func = [&](NodePtr _head) {
      if (_head == nullptr)
        return;
      if (_head->left == nullptr && _head->right == nullptr) {
        re.insert(_head);
        return;
      }
      func(_head->left);
      func(_head->right);
    };
    func(head);
    return re;
  }

  // 销毁树
  void destroy_tree() override {}
  bool empty() const override { return head == nullptr; }
};

#endif