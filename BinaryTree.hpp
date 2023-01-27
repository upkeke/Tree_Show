// author : keke
// date : 2023/01/27
#pragma once
#ifndef __BINARYTREE__
#define __BINARYTREE__
#include <queue>
#include <vector>
using std::queue;
enum class NodeColor {
  yellow,
  green,
  red,
  black,
};
struct Pos {
  int row;
  int col;                             // 也是节点的深度
  int height = 0;                      // 节点的高度
  NodeColor color = NodeColor::yellow; // 红黑树专用

  Pos() : row(0), col(0) {}
  Pos(NodeColor color) : row(0), col(0), color(color) {}
  void setPos(int x, int y);
  bool isRedn(Pos *head);
  void setColor(NodeColor _color);
  virtual ~Pos() { ; }
};

template <class T> struct Node {
  // Node(const Node &) = delete;
  // Node(Node &&) = delete;
  // Node &operator=(const Node &) = delete;
  // Node &operator=(Node &&) = delete;
  Node(const T &val, Node *left = nullptr, Node *right = nullptr)
      : val(val), left(left), right(right) {}
  Node() : Node(T{}) {}
  T val;
  Node *left;
  Node *right;
};
template <class T> struct BinaryTree {
  enum class Direction {
    left,
    right,
  };
  using NodePtr = Node<T> *;
  using Node_ = Node<T>;
  //using order = std::queue<NodePtr>;  
  using orderList = std::vector<NodePtr>;
  NodePtr head = nullptr;
  // 创建树
  virtual void create_tree() = 0;
  // 拷贝树 ---深拷贝
  virtual void copy_tree(const BinaryTree &other) = 0;
  // 前序遍历
  // 返回值 order是一个队列，里面存的元素是节点指针
  // 相当于之前是printf，现在要按照顺序push遍历到的节点指针
  virtual queue<NodePtr> foreach_front() const = 0;
  // 中序遍历 返回值 order 同上
  virtual queue<NodePtr> foreach_mid() const = 0;
  // 后序遍历 返回值 order 同上
  virtual queue<NodePtr> foreach_back() const = 0;
  // 层级遍历 返回值 order 同上
  virtual queue<NodePtr> foreach_ceng() const = 0;
  // 查找节点
  // 返回值 查找节点的地址，没有找到返回{}
  virtual std::vector<NodePtr> find_node(const T &_val) const = 0;
  // 插入节点
  // 参数 _val是插入的值，base是插入节点的父节点，
  // dirc是指要插入到父节点的左子节点还是右子节点
  // 返回值 插入节点的地址，插入失败返回nullptr
  virtual NodePtr insert_node(const T &_val, NodePtr base, Direction dirc) = 0;
  // 删除指定节点。可能这个值有多个节点指针，将它们都放在队列中
  virtual size_t delete_node(const T &_val) = 0;
  // 深度
  virtual size_t depth() const = 0;
  // 反转左右子树
  virtual void *reverse_tree() = 0;
  // 销毁树
  virtual void destroy_tree() = 0;
  // 空
  virtual bool empty()const =0;
  virtual ~BinaryTree() {}
};

#endif