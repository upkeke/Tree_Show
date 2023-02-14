
#pragma once
#ifndef __BINARYTREESTR__
#define __BINARYTREESTR__

#include "FuncForHeadNode.h"
#include <NodeStr.hpp>
#include <QPointF>
#include <functional>
namespace sbt {

struct BinaryTreeStr : BinaryTree<PosStrNode> {
  using typename BinaryTree<PosStrNode>::Direction;
  using typename BinaryTree<PosStrNode>::val_type;
  using BaseNodeStr = _baseNode<_string>;
  using BaseNodeStrPtr = BaseNodeStr *;
  using Node = PosStrNode;
  using NodePtr = PosStrNode *;

  BinaryTreeStr() = default;
  template <node_able NodeTy> explicit BinaryTreeStr(NodeTy *_head) {
    init_tree(_head);
    if (head != nullptr)
      head->isHead = true;
  }
  explicit BinaryTreeStr(NodePtr _head) {
    this->head = _head;
    auto tp = foreach_mid();
    allNode.insert(tp.begin(), tp.end());
    sbt::update_xy(head, offset);
    if (head != nullptr)
      head->isHead = true;
  }
  // 调试用
  virtual void create_tree() override {
    // vector<int> data = get_vector_norepeat(10);
    _SPC vector<_string> data(7);
    for (int i = 0; i < 7; ++i) {
#if HAS_QSTRING
      data[i] = _string::number(i);
#else
      data[i] = std::to_string(i);
#endif
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
    auto tp = foreach_mid();
    allNode.insert(tp.begin(), tp.end());
    sbt::update_xy(head, offset);
    if (head != nullptr)
      head->isHead = true;
  }
  /**
   * @brief 传入其他类型的Node指针
   *
   复制传入的二叉树头节点，并转为Node<_string>*类型，
   同时根据scale放大节点的row和col
   * @tparam tp  传入指针的val的类型
   * @param nodeptr 传入的根节点
   */
  template <node_able NodeTy> void init_tree(NodeTy *nodeptr) {
    // 后序遍历复制
    std::function<NodePtr(NodeTy *)> func = [&](NodeTy *_head) -> NodePtr {
      if (_head == nullptr)
        // return static_cast<NodePtr>(nullptr) ;
        return nullptr;
      NodePtr _left = func(_head->left);
      NodePtr _right = func(_head->right);
#if HAS_QSTRING
      _string str = val_to_qstring(_head->val);
#else
      _string str = val_to_string(_head->val);
#endif
      NodePtr re = new Node(str, _left, _right);
      this->allNode.insert(re);
      return re;
    };
    head = func(nodeptr);
    // 修正节点的横纵坐标
    sbt::update_xy(head, offset);
    if (head != nullptr)
      head->isHead = true;
  }
  void update_xy() const { sbt::update_xy(head, offset); }
  std::unordered_set<NodePtr> getAllNode() const { return allNode; }
  virtual NodePtr get_head() const override { return head; }
  _SPC vector<NodePtr> foreach_front() const override {
    _SPC vector<NodePtr> re;
    sbt::foreach_front(
        head,
        [](NodePtr cur, _SPC vector<NodePtr> &_re) { _re.push_back(cur); }, re);
    return re;
  }
  _SPC vector<NodePtr> foreach_mid() const override {
    _SPC vector<NodePtr> re;

    sbt::foreach_mid(
        head,
        [](NodePtr cur, _SPC vector<NodePtr> &_re) { _re.push_back(cur); }, re);
    return re;
  }
  _SPC vector<NodePtr> foreach_back() const override {
    _SPC vector<NodePtr> re;
    sbt::foreach_back(
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
        base->Left()->setXYColor(base->col - 1, base->row + 1, base->color);
        allNode.insert(base->Left());
        return base->Left();
      }
      if (base->right == nullptr && dirc == Direction::right) {
        base->right = new Node(_val);
        // base->right->setPosColor(base->col + 1, base->row + 1, base->color);
        base->Right()->setXYColor(base->col + 1, base->row + 1, base->color);
        allNode.insert(base->Right());
        return base->Right();
      }
    }
    return nullptr;
  }
  /**
   * @brief 如果节点的左子树或者右子树为空，可插入
   *
   * @param derived
   * @param base
   * @param dirc
   */
  void insert_node(NodePtr derived, NodePtr base, Direction dirc) {
    switch (dirc) {
    case BinaryTree<PosStrNode>::Direction::left:
      base->left = derived;
      break;
    case BinaryTree<PosStrNode>::Direction::right:
      base->right = derived;
      break;
    }
    derived->color = base->color;
    derived->col = base->col + 1;
  }
  bool delete_node(NodePtr order) override {
    if (order == nullptr || order->left != nullptr || order->right != nullptr)
      return false;
    bool re = false;
    // 先序遍历
    sbt::foreach_front(
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
    sbt::foreach_front(head,
                       [](NodePtr cur) { std::swap(cur->left, cur->right); });
    sbt::update_xy(head, offset);
  }
  std::unordered_set<NodePtr> get_leaves() const override {
    std::unordered_set<NodePtr> re;
    sbt::foreach_front(
        head,
        [](NodePtr cur, std::unordered_set<NodePtr> &_re) {
          if (cur->left == nullptr && cur->right == nullptr) {
            _re.insert(cur);
          }
        },
        re);
    return re;
  }
  // 销毁树
  void destroy_tree() override {
    sbt::foreach_back(head, [](NodePtr cur) { delete cur; });
    head = nullptr;
  }
  bool empty() const override { return head == nullptr; }
  size_t size() const override {
    size_t count = 0;
    sbt::foreach_front(
        head, [](NodePtr cur, size_t &count) { count++; }, count);
    return count;
  }
  ~BinaryTreeStr() { destroy_tree(); }
  /**
    * @brief 设置偏移量
    调用这个函数后要调用updatePos，是所有的节点都调用，
    *
    * @param offset
    */
  void setOffset(const QPointF &offset) { this->offset = offset; }

private:
  NodePtr head = nullptr;
  std::unordered_set<NodePtr> allNode;
  /**
  * @brief 偏移量
  节点在场景中的坐标会和这个偏移量相加，方便二叉树位置的再调整
  *
  */
  QPointF offset{0, 0};
  // setOffset
};
using Tree = BinaryTreeStr;
using TreePtr = BinaryTreeStr *;
} // namespace sbt

#endif