//date : 2023/01/30 
#pragma once
#ifndef __TREEHEAD__
#define __TREEHEAD__

#include <BinaryTree.hpp>
#include <functional>
#include <common_func.hpp>
#include<data_source.h>
#include <vector>
#include<queue>
using std::queue;
using std::vector;

#if STD__CXX >= CXX_20
template <class T> struct TreeHead : BinaryTree<T> {};
#else
template <class T> struct MyTree : BinaryTree<T> {};
#endif

template <> struct TreeHead<Node<int>> : BinaryTree<Node<int>> {
  using T = Node<int>;
  using typename BinaryTree<T>::Node_;
  using typename BinaryTree<T>::NodePtr;
  using typename BinaryTree<T>::Direction;
  using typename BinaryTree<T>::val_type;
  NodePtr head;
  TreeHead() = default;
  TreeHead(const TreeHead &other) { copy_tree(other); }
  TreeHead(TreeHead &&) = default;
  explicit TreeHead(NodePtr _head) {
    TreeHead tp;
    tp.head = _head;
    copy_tree(tp);
    tp.head = nullptr;
  }
  TreeHead &operator=(const TreeHead &) = default;
  TreeHead &operator=(TreeHead &&) = default;

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
    vector<NodePtr> re;
    ::foreach_front(
        head, [](NodePtr cur, vector<NodePtr> &_re) { _re.push_back(cur); },
        re);
    return re;
  }
  vector<NodePtr> foreach_mid() const override {
    vector<NodePtr> re;
    ::foreach_mid(
        head, [](NodePtr cur, vector<NodePtr> &_re) { _re.push_back(cur); },
        re);
    return re;
  }
  // 后序遍历 如果取出的上一个节点是栈顶的right，就可以取出栈顶
  // 如果不是 就进入右子树
  vector<NodePtr> foreach_back() const override {
    vector<NodePtr> re;
    ::foreach_back(
        head, [](NodePtr cur, vector<NodePtr> &_re) { _re.push_back(cur); },
        re);
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
  NodePtr insert_node(const val_type &_val, NodePtr base,
                      Direction dirc) override {
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
  bool delete_node(NodePtr order) override {
    if (order == nullptr || order->left != nullptr || order->right != nullptr)
      return false;
    bool re = false;
    // 先序遍历
    ::foreach_front(
        head,
        [](NodePtr cur, bool &_re, NodePtr _order) {
          if (cur->left == _order || cur->right == _order) {
            if (cur->left == _order) {
              cur->left = nullptr;
            } else {
              cur->right = nullptr;
            }
            _re = true;
            delete _order;
          }
        },
        re, order);
    return re;
  }
  // 深度
  size_t depth() const override {
    std::function<size_t(NodePtr)> func = [&](NodePtr _head) -> size_t {
      if (_head == nullptr)
        return 0;
      size_t left = func(_head->left);
      size_t right = func(_head->right);
      return std::max(left, right) + 1;
    };
    return func(head);
  }
  // 反转左右子树
  void reverse_tree() override {
    ::foreach_front(head,
                    [](NodePtr cur) { std::swap(cur->left, cur->right); });
  }
  std::set<NodePtr> get_leaves() const override {
    std::set<NodePtr> re;
    ::foreach_front(
        head,
        [](NodePtr cur, std::set<NodePtr> &_re) {
          if (cur->left == nullptr && cur->right == nullptr) {
            _re.insert(cur);
          }
        },
        re);
    return re;
  }
  // 销毁树
  void destroy_tree() override {
    ::foreach_back(head, [](NodePtr cur) { delete cur; });
  }
  bool empty() const override { return head == nullptr; }
};

#endif