// author : keke
// date : 2023/02/05
#pragma once
#ifndef __BINARYTREESTR__
#define __BINARYTREESTR__

#include "FuncForTreeStr.h"
#include <BinaryTree.hpp>
#include <QPointF>
#include <functional>


//extern void update_xy(PosStrNode *head, int scale_row, int scale_col);
struct BinaryTreeStr : BinaryTree<PosStrNode> {

  // using typename BinaryTree<PosStrNode>::Node;
  // using typename BinaryTree<PosStrNode>::NodePtr;
  using typename BinaryTree<PosStrNode>::Direction;
  using typename BinaryTree<PosStrNode>::val_type;
  using BaseNodeStr = _baseNode<_string>;
  // using _baseNodePtr =typename _baseNode<_string> *;
  using BaseNodeStrPtr = BaseNodeStr *;
  using Node = PosStrNode;
  using NodePtr = PosStrNode *;
  NodePtr head = nullptr;
  /**
   * @brief 放大比例
   * 对于Node的row和col不能直接使用，需要进行方法
   */
  int scale_row = 40;
  int scale_col = 60;
  BinaryTreeStr() = default;
  template <str_able tp> explicit BinaryTreeStr(_baseNode<tp> *_head) {
    init_tree(_head);
  }
  // 调试用
  virtual void create_tree() override {
    // vector<int> data = get_vector_norepeat(10);
    _SPC vector<_string> data(7);
    for (int i = 0; i < 7; ++i) {
      data[i] = QString::number(i);
    }
    head = new Node(data[0]);
    _SPC queue<NodePtr> qe;
    qe.push(head);
    size_t i = 1;
    while (!qe.empty()) {
      if (i == data.size())
        break;
      NodePtr temp = qe.front();
      temp->left = new Node(data[i++]);
      // qe.push(static_cast<NodePtr>(temp->left));
      qe.push(temp->Left());
      if (i == data.size())
        break;
      temp->right = new Node(data[i++]);
      // qe.push(static_cast<NodePtr>(temp->right));
      qe.push(temp->Right());
      qe.pop();
    }
    ::update_xy(head, scale_row, scale_col);
    //::update_xy(head, scale_row, scale_col);
  }
  /**
   * @brief 传入其他类型的Node指针
   *
   复制传入的二叉树头节点，并转为Node<_string>*类型，
   同时根据scale放大节点的row和col
   * @tparam tp  传入指针的val的类型
   * @param nodeptr 传入的根节点
   */
  template <str_able tp> void init_tree(_baseNode<tp> *nodeptr) {
    // 后序遍历复制
    std::function<NodePtr(_baseNode<tp> *)> func = [&](_baseNode<tp> *_head) {
      if (_head == nullptr)
        return _head;
      NodePtr _left = func(_head->left);
      NodePtr _right = func(_head->right);
#if HAS_QSTRING
      _string str = val_to_qstring(_head->val);
#else
      _string str = val_to_string(_head->val);
#endif
      NodePtr re = new Node(str, _left, _right);
      return re;
    };
    head = func(nodeptr);
    // 修正节点的横纵坐标
    ::update_xy(head, scale_row, scale_col);
  }
  void set_scale(int x, int y) {
    scale_row = x;
    scale_col = y;
    ::update_xy(head, scale_row, scale_col);
  }
  void update_xy() { ::update_xy(head, scale_row, scale_col); }
  virtual NodePtr get_head() const override { return head; }
  _SPC vector<NodePtr> foreach_front() const override {
    _SPC vector<NodePtr> re;

    ::foreach_front(
        head,
        [](NodePtr cur, _SPC vector<NodePtr> &_re) { _re.push_back(cur); }, re);
    return re;
  }
  _SPC vector<NodePtr> foreach_mid() const override {
    _SPC vector<NodePtr> re;

    ::foreach_mid(
        head,
        [](NodePtr cur, _SPC vector<NodePtr> &_re) { _re.push_back(cur); }, re);
    return re;
  }
  // 后序遍历 如果取出的上一个节点是栈顶的right，就可以取出栈顶
  // 如果不是 就进入右子树
  _SPC vector<NodePtr> foreach_back() const override {
    _SPC vector<NodePtr> re;
    ::foreach_back(
        head,
        [](NodePtr cur, _SPC vector<NodePtr> &_re) { _re.push_back(cur); }, re);
    return re;
  }
  _SPC vector<NodePtr> foreach_ceng() const override {
    if (empty())
      return {};
    _SPC vector<NodePtr> re;
    _SPC queue<NodePtr> qe;
    qe.push(head);
    while (!qe.empty()) {
      NodePtr temp = qe.front();
      re.push_back(temp);
      if (temp->left != nullptr)
        // qe.push(temp->left);
        qe.push(temp->Left());
      if (temp->right != nullptr)
        // qe.push(temp->right);
        qe.push(temp->Right());
      qe.pop();
    }
    return re;
  }

  bool find_node(NodePtr ptr) const {
    if (ptr == nullptr)
      return false;
    _SPC vector<NodePtr> order = foreach_front();
    for (auto item : order) {
      if (item == ptr)
        return true;
    }
    return false;
  }
  _SPC vector<NodePtr> find_node(const val_type &_val) const override {
    _SPC vector<NodePtr> re;
    // NRVO order和函数中re是同一变量
    _SPC vector<NodePtr> order = foreach_front();
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
        base->left = new Node(_val);
        // base->left->setPosColor(base->col - 1, base->row + 1, base->color);
        base->Left()->setPosColor(base->col - 1, base->row + 1, base->color);
        return base->Left();
      }
      if (base->right == nullptr && dirc == Direction::right) {
        base->right = new Node(_val);
        // base->right->setPosColor(base->col + 1, base->row + 1, base->color);
        base->Right()->setPosColor(base->col + 1, base->row + 1, base->color);
        return base->Right();
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
      size_t left = func(_head->Left());
      size_t right = func(_head->Right());
      return std::max(left, right) + 1;
    };
    return func(head);
  }
  // 反转左右子树
  void reverse_tree() override {
    ::foreach_front(head,
                    [](NodePtr cur) { std::swap(cur->left, cur->right); });
    ::update_xy(head, scale_row, scale_col);
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
  size_t size() const override {
    size_t count = 0;
    ::foreach_front(
        head, [](NodePtr cur, size_t &count) { count++; }, count);
    return count;
  }
};

#endif