

#pragma once
#ifndef __NODESTR__
#define __NODESTR__

#include "NodeTemp.hpp"
#include <unordered_set>

/*------------------------------------------------------------
--------------------------------------------------------------
--------------------------------------------------------------
只要你写的节点满足下面要求,即可打印二叉树
1. 二叉树的单个节点的类型继承自Node，
2. Node的模板参数满足 约束 qstr_able
，即约束保证T是基本类型，或者能够隐式转换为QString的自定义类型

下面的BinaryTree要实现的方法仅供参考，可以不用这个
------------------------------------------------------------
--------------------------------------------------------------
--------------------------------------------------------------
*/
#include <QPointF>
namespace sbt {
// class GrapNodeItem;
using NodeColor = Qt::GlobalColor;
struct PosStrNode : _baseNode<_string> {
  using BaseNode = _baseNode<_string>;
  using BaseNodePtr = _baseNode<_string> *;
  using _baseNode<_string>::_baseNode;
  int row = 0;
  int col = 0;
  NodeColor color = NodeColor::yellow;
  PosStrNode() = default;
  explicit PosStrNode(NodeColor color) : BaseNode() { this->color = color; }
  PosStrNode(int row, int col, NodeColor color)
      : row(row), col(col), color(color) {}
  PosStrNode(const QPointF &pos, NodeColor color)
      : row(pos.x()), col(pos.y()), color(color) {}
  void setPos(int x, int y) {
    row = x;
    col = y;
  }
  void setPos(const QPointF &pos) {
    row = pos.x();
    col = pos.y();
  }
  QPointF Pos() const { return QPointF(row, col); }

  void setColor(NodeColor _color) { color = _color; }

  void setPosColor(int row, int col, NodeColor color) {
    this->row = row;
    this->col = col;
    this->color = color;
  }
  void setPosColor(const PosStrNode &other) {
    row = other.row;
    col = other.col;
    color = other.color;
  }
  /**
   * @brief 需要强转一下
   如果直接this->left 的类型是_baseNode<_string> *;
   *
   * @return PosStrNode*
   */
  PosStrNode *Left() { return static_cast<PosStrNode *>(left); }
  PosStrNode *Right() { return static_cast<PosStrNode *>(right); }
};
/**
 * @brief 项目内部所有的节点的指针的val都是_string
 *
 */
using NodePtr = PosStrNode *;
using Node = PosStrNode;
using BaseNodePtr = _baseNode<_string> *;

template <node_able NodeT> struct BinaryTree {
  enum class Direction {
    left,
    right,
  };
  using val_type = typename NodeT::tp;
  using Node = NodeT;
  using NodePtr = NodeT *;
  virtual void create_tree() = 0;
  // 获得头节点
  virtual NodePtr get_head() const = 0;
  // 前序遍历
  // 返回值 order是一个队列，里面存的元素是节点指针
  // 相当于之前是printf，现在要按照顺序push遍历到的节点指针
  virtual _SPC vector<NodePtr> foreach_front() const = 0;
  // 中序遍历 返回值 order 同上
  virtual _SPC vector<NodePtr> foreach_mid() const = 0;
  // 后序遍历 返回值 order 同上
  virtual _SPC vector<NodePtr> foreach_back() const = 0;
  // 层级遍历 返回值 order 同上
  virtual _SPC vector<NodePtr> foreach_ceng() const = 0;
  // 查找节点
  // 返回值 查找节点的地址，没有找到返回{}
  virtual _SPC vector<NodePtr> find_node(const val_type &_val) const = 0;
  // 插入节点
  // 参数 _val是插入的值，base是插入节点的父节点，base只能是叶子节点
  // dirc是指要插入到父节点的左子节点还是右子节点
  // 返回值 插入节点的地址，插入失败返回nullptr
  virtual NodePtr insert_node(const val_type &_val, NodePtr base,
                              Direction dirc) = 0;
  // 删除指定节点。只能删除叶子节点
  virtual bool delete_node(NodePtr order) = 0;
  // 深度
  virtual size_t depth() const = 0;
  // 反转左右子树
  virtual void reverse_tree() = 0;
  // 获得所有叶子
  virtual std::unordered_set<NodePtr> get_leaves() const = 0;
  // 销毁树
  virtual void destroy_tree() = 0;
  // 空
  virtual bool empty() const = 0;
  virtual size_t size() const = 0;
  virtual ~BinaryTree() {}
};
} // namespace sbt
#endif