
#pragma once
#ifndef __HEADNODE__
#define __HEADNODE__

#include "FuncForHeadNode.h"
#include "QStrNode.hpp"

namespace sbt {
/**
 * @brief 传入其他类型的Node指针
 *
 复制传入的二叉树头节点，并转为Node<QString>*类型，
 同时根据scale放大节点的row和col
 * @tparam tp  传入指针的val的类型
 * @param nodeptr 传入的根节点
 */
template <node_able NodeTy> NodePtr init_tree(NodeTy *nodeptr) {
  // 后序遍历复制
  std::function<NodePtr(NodeTy *)> func = [&](NodeTy *_head) -> NodePtr {
    if (_head == nullptr)
      // return static_cast<NodePtr>(nullptr) ;
      return nullptr;
    NodePtr _left = func(_head->left);
    NodePtr _right = func(_head->right);
    QString str = val_to_qstring(_head->val);
    NodePtr re = new Node(str, _left, _right);
    // this->allNode.insert(re);
    return re;
  };
  NodePtr head = func(nodeptr);
  // 修正节点的横纵坐标
  sbt::update_xy(head, QPointF{0, 0});
  return head;
}
NodePtr create_tree();
_SPC vector<NodePtr> foreach_front_v(NodePtr);
_SPC vector<NodePtr> foreach_mid_v(NodePtr);
_SPC vector<NodePtr> foreach_back_v(NodePtr);
_SPC vector<NodePtr> foreach_ceng_v(NodePtr);

// 获得所有叶子
_SPC vector<NodePtr> get_leaves_v(NodePtr);
void insert_node(NodePtr derived, NodePtr base, bool isLeft);
void delete_tree(NodePtr head);


} // namespace sbt

#endif