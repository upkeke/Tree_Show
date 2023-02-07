﻿
#pragma once
#ifndef __FUNCFORTREESTR__
#define __FUNCFORTREESTR__

#include <BinaryTree.hpp>
#include <QPointF>
#include <QString>
#include <concepts>
#include <string>

QPointF operator*(const PosStrNode &ps, const QPointF &pt);
QPointF operator*(const QPointF &pt, const PosStrNode &ps);


/**
 * @brief 其满足str_able约束的其他类型的值转换为QString
 * 
 * @tparam T 
 * @param val 
 * @return QString 
 */
template <str_able T> QString val_to_qstring(const T &val) {
  if constexpr (std::is_arithmetic_v<T>) {
    if constexpr (std::is_same_v<bool, T>) {
      return val ? "true" : "false";
    } else if constexpr (std::is_same_v<char, T>) {
      return QString(1, val);
    } else {
      return QString::number(val);
    }
  } else if constexpr (std::is_convertible_v<T, std::string>) {
    return QString::fromStdString(val);
  } else {
    if constexpr (std::is_same_v<QChar, T>)
      return QString(1, val);
    else
      return val;
  }
}
/**
 * @brief 其满足str_able约束的其他类型的值转换为string
 * 
 * @tparam T 
 * @param val 
 * @return std::string 
 */
template <str_able T> std::string val_to_string(const T &val) {
  if constexpr (std::is_arithmetic_v<T>) {
    if constexpr (std::is_same_v<bool, T>) {
      return val ? "true" : "false";
    } else if constexpr (std::is_same_v<char, T>) {
      return string(1, val);
    } else {
      return std::to_string(val);
    }
  } else {
    return val;
  }
}

/// @brief
/// @tparam Func
/// @tparam ...Args
/// @param head 根节点
/// @param func 回调函数
/// @param ...args 参数包
/// 参数包，注意第一个参数是遍历二叉树遍历到的当前节点，如果要返回值，第二个参数传引用
template <class Func, class... Args>
void foreach_front(NodePtr head, Func func, Args &&...args) {
  _SPC stack<NodePtr> sk;
  NodePtr temp = head;
  while (!sk.empty() || temp != nullptr) {
    while (temp != nullptr) {
      func(temp, std::forward<Args>(args)...);
      sk.push(temp);
      // temp = temp->left;
      temp = temp->Left();
    }
    if (!sk.empty()) {
      temp = sk.top();
      sk.pop(); // 去掉中间节点
      // temp = temp->right;
      temp = temp->Right();
    }
  }
}
/**
 * @brief 中序遍历
 * 
 * @tparam Func 
 * @tparam Args 
 * @param head 
 * @param func 
 * @param args 
 */
template <class Func, class... Args>
void foreach_mid(NodePtr head, Func func, Args &&...args) {
  _SPC stack<NodePtr> sk;
  NodePtr temp = head;
  while (!sk.empty() || temp != nullptr) {
    while (temp != nullptr) {
      sk.push(temp);
      // temp = temp->left;
      temp = temp->Left();
    }
    if (!sk.empty()) {
      temp = sk.top();
      // re.push_back(temp); // 相当于printf
      func(temp, std::forward<Args>(args)...);
      sk.pop(); // 去掉中间节点
      // temp = temp->right;
      temp = temp->Right();
    }
  }
}
/**
 * @brief 后序遍历
 * 
 * @tparam Func 
 * @tparam Args 
 * @param head 
 * @param func 
 * @param args 
 */
template <class Func, class... Args>
void foreach_back(NodePtr head, Func func, Args &&...args) {
  _SPC stack<NodePtr> sk;
  NodePtr temp = head;
  NodePtr last = head;
  while (temp != nullptr || !sk.empty()) {
    while (temp != nullptr) {
      sk.push(temp);
      // temp = temp->left;
      temp = temp->Left();
    }
    temp = sk.top();
    if (temp->right != nullptr) {
      if (temp->right != last) {
        // temp = temp->right;
        temp = temp->Right();
        continue;
      }
    }
    last = temp;
    func(temp, std::forward<Args>(args)...);
    temp = nullptr; // 避免重复访问左子节点
    sk.pop();
  }
}
/**
 * @brief 调整节点的横坐标。使用场景坐标
 * 
 * @param head 
 * @param scale_row 比例尺
 */
void update_row(PosStrNode *head, int scale_row);
/**
 * @brief 调整节点的纵坐标。使用场景坐标
 * 
 * @param head 
 * @param scale_col 
 */
void update_col(PosStrNode *head, int scale_col);
/**
 * @brief 调整横纵坐标
 * 
 * @param head 
 * @param scale_row 
 * @param scale_col 
 */
void update_xy(PosStrNode *head, int scale_row = 40, int scale_col = 60);

#endif