﻿// author : keke
// date : 2023/01/27
#pragma once
#ifndef __BINARYTREE__
#define __BINARYTREE__
#include <QString>
#include <queue>
#include <set>
#include <type_traits>
#include <vector>


using std::vector;
#ifndef NODECOLOR
#define NODECOLOR
enum class NodeColor {
  yellow,
  green,
  pink,
  black,
};
#endif
struct Pos {
  int row;
  int col;
  NodeColor color = NodeColor::yellow;
  Pos() : row(0), col(0) {}
  Pos(NodeColor color) : Pos() { this->color = color; }
  void setPos(int x, int y) {
    row = x;
    col = y;
  }
  bool isRedn(Pos *head) { return head->color == NodeColor::pink; }
  void setColor(NodeColor _color) { color = _color; }
  virtual ~Pos() {}
};
template <class T> struct Node : Pos {
  Node(const T &val, Node *left = nullptr, Node *right = nullptr)
      : val(val), left(left), right(right) {}
  Node() : Node(T{}) {}
  T val;
  Node *left;
  Node *right;
  using tp = T;
};
//约束保证T是基本类型，或者能够隐式转换为QString的自定义类型
template <class T>
concept qstr_able =
    std::is_arithmetic_v<T> || std::is_convertible_v<T, QString>;
// 约束Node必须是Node或者Node的子类，且Node的val必须是算术类型或者能够隐式转化为string
template <class T>
concept node_able = requires {
                      requires std::derived_from<T, Node<typename T::tp>>;
                    } && qstr_able<typename T::tp>;



/*------------------------------------------------------------
--------------------------------------------------------------
--------------------------------------------------------------
只要你写的节点满足下面要求,即可打印二叉树
1. 二叉树的单个节点的类型继承自Node，
2. Node的模板参数满足 约束 qstr_able ，即约束保证T是基本类型，或者能够隐式转换为QString的自定义类型

下面的BinaryTree要实现的方法仅供参考，可以不用这个
------------------------------------------------------------
--------------------------------------------------------------
--------------------------------------------------------------
*/

template <node_able NodeT> struct BinaryTree {
  enum class Direction {
    left,
    right,
  };

  using val_type = typename NodeT::tp;
  using Node_ = NodeT;
  using NodePtr = NodeT *;
  virtual void create_tree() = 0;
  // 拷贝树 ---深拷贝
  virtual void copy_tree(const BinaryTree &other) = 0;
  // 获得头节点
  virtual NodePtr get_head() const = 0;
  // 前序遍历
  // 返回值 order是一个队列，里面存的元素是节点指针
  // 相当于之前是printf，现在要按照顺序push遍历到的节点指针
  virtual vector<NodePtr> foreach_front() const = 0;
  // 中序遍历 返回值 order 同上
  virtual vector<NodePtr> foreach_mid() const = 0;
  // 后序遍历 返回值 order 同上
  virtual vector<NodePtr> foreach_back() const = 0;
  // 层级遍历 返回值 order 同上
  virtual vector<NodePtr> foreach_ceng() const = 0;
  // 查找节点
  // 返回值 查找节点的地址，没有找到返回{}
  virtual vector<NodePtr> find_node(const val_type &_val) const = 0;
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
  virtual std::set<NodePtr> get_leaves() const = 0;
  // 销毁树
  virtual void destroy_tree() = 0;
  // 空
  virtual bool empty() const = 0;
  virtual ~BinaryTree() {}
};

#endif