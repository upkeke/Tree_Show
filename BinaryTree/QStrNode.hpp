
#pragma once
#ifndef __QSTRNODE__
#define __QSTRNODE__

#include <NodeAble.hpp>
#include <QPointF>
#include <QString>
#include <unordered_set>

namespace sbt {
// class GrapNodeItem;
using NodeColor = Qt::GlobalColor;
struct PosStrNode {
  // using BaseNode = _baseNode<QString>;
  // using BaseNodePtr = _baseNode<QString> *;
  // using _baseNode<QString>::_baseNode;
  /**
   * @brief 拷贝构造移动构造赋值运算都是默认，浅拷贝，
   不能资源的释放靠tree维护
   *
   */
  PosStrNode() = default;
  explicit PosStrNode(const QString &val, PosStrNode *left = nullptr,
                      PosStrNode *right = nullptr)
      : val(val), left(left), right(right) {}
  PosStrNode(int row, int col, NodeColor color)
      : row(row), col(col), color(color) {}
  PosStrNode(const QPointF &pos, NodeColor color) : pos(pos), color(color) {}

  void setPos(const QPointF &pos) { this->pos = pos; }
  void toScenePos(const QPointF &offset = QPointF{0, 0}) {
    pos = QPointF(row * scale.x(), col * scale.y()) + offset;
  }
  QPointF Pos() const { return pos; }
  /**
   * @brief 图元后序可能会移动，移动后的位置，求出偏移量
   *
   */
  QPointF getOffsetByNowPos() {
    return pos - QPointF(row * scale.x(), col * scale.y());
  }
  static void setScale(const QPointF &scale) { PosStrNode::scale = scale; }
  /**
   * @brief 设置 衡中原始坐标，而不是场景坐标
   *
   * @param row 原始坐标 row
   * @param col 原始坐标 col
   * @param color 颜色
   */
  void setXYColor(int row, int col, NodeColor color) {
    this->row = row;
    this->col = col;
    this->color = color;
  }

  QString val{};
  PosStrNode *left = nullptr;
  PosStrNode *right = nullptr;

  int row = 0;
  int col = 0;
  NodeColor color = NodeColor::yellow;
  /**
   * @brief 避免头节点和其他树的叶子进行碰撞检测
   * 
   */
  PosStrNode *head = nullptr;
  bool isHead = false;

private:
  /**
   * @brief 节点场景坐标
   注意pos和row和col的区别
   pos是根据row和获得，但只会设置一次，之后pos不归row和col管，二者是弱绑定
   updatePos函数可以再次绑定一下
   * 对于Node的row和col不能直接使用，需要进行方法
   */
  QPointF pos{0, 0};
  // 场景中坐标
  /**
  * @brief 比例尺
  row和col向pos转换的比例
  *
  */
  inline static QPointF scale{40, 60}; // 比例尺
};
/**
 * @brief 项目内部所有的节点的指针的val都是QString
 *
 */
using NodePtr = PosStrNode *;
using Node = PosStrNode;

template <class T>
concept node_ableA = node_able<T> || std::same_as<T, Node>;

/**
 * @brief 仅供参考
 *
 * @tparam NodeT
 */
template <node_ableA NodeT> struct BinaryTree {
  enum class Direction {
    left,
    right,
  };
  using val_type = decltype(NodeT::val); // typename NodeT::value_tp;
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