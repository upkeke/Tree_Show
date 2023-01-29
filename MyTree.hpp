// author : keke
// date : 2023/01/27
#pragma once

#include <algorithm>
#include <vector>
#ifndef __MYTREE__
#define __MYTREE__
#include <BinaryTree.hpp>
#include <concepts>
#include <functional>
#include <some_func.h>
#include <stack>

using std::queue;
using std::stack;
using std::vector;

//_修正节点横坐标
template <class T> void update_row(Node<T> *head, int &index) {
  if (head == nullptr)
    return;
  update_row(head->left, index);
  head->row = index++;
  update_row(head->right, index);
}
template <class T> int xxx1(Node<T> *k) { return k->val; }
//_修正节点纵坐标
template <class T> void update_col(Node<T> *head) {
  if (head == nullptr)
    return;
  queue<Node<T> *> Q;
  Q.push(head);
  Q.push(0);
  int index = 0;
  do {
    Node<T> *node = Q.front();
    Q.pop();
    if (node) {
      node->col = index;
      // cout << node->val << " ";
      if (node->left)
        Q.push(node->left);
      if (node->right)
        Q.push(node->right);
    } else if (!Q.empty()) {
      Q.push(0);
      ++index;
    }
  } while (!Q.empty());
}
template <class T> void update_xy(Node<T> *head) {
  int index = 0;
  update_row(head, index);
  update_col(head);
}
#if STD__CXX >= CXX_20
template <node_able T> struct MyTree : BinaryTree<T> {};
#else
template <class T> struct MyTree : BinaryTree<T> {};
#endif

template <> struct MyTree<Node<int>> : BinaryTree<Node<int>> {
  using T = Node<int>;
  using typename BinaryTree<T>::Node_;
  using typename BinaryTree<T>::NodePtr;
  using typename BinaryTree<T>::Direction;
  using typename BinaryTree<T>::val_type;
  NodePtr head;
  MyTree() = default;
  MyTree(const MyTree &other) { copy_tree(other); }
  MyTree(MyTree &&) = default;
  explicit MyTree(NodePtr _head) {
    MyTree tp;
    tp.head = _head;
    copy_tree(tp);
    tp.head = nullptr;
  }
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
    std::function<void(NodePtr)> func = [&](NodePtr _head) {
      if (_head == nullptr)
        return;
      if (_head->left == order || _head->right == order) {
        if (_head->left == order) {
          _head->left = nullptr;
        } else {
          _head->right = nullptr;
        }
        re = true;
        delete order;
      }
    };
    func(head);
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