
//author : keke
//date : 2023/02/04 
#pragma once
#ifndef __COMMON_FUNC__
#define __COMMON_FUNC__



#include <BinaryTree.hpp>
#include <concepts>


template <qstr_able T> QString val_to_qstring(const T &val) {
  if constexpr (std::is_arithmetic_v<T>) {
    if constexpr (std::is_same_v<bool, T>) {
      return val ? "true" : "false";
    } else if constexpr (std::is_same_v<char, T>) {
      return QString(1, val);
    } else {
      return QString::number(val);
    }
  } else {
    if constexpr (std::is_same_v<QChar, T>)
      return QString(1, val);
    else
      return val;
  }
}
template <class T>
concept NodePtrAble = requires(T ptr) {
                        // 这儿不知道怎么弄，直接是ptr->left，能正常运行，但是爆红线，因为same_as只接受一个纯右值
                        // 我只好加1让这个表达式转换为纯右值
                        { ptr->left + 1 } -> std::same_as<T>;
                        { ptr->right + 1 } -> std::same_as<T>;
                        ptr->val;
                      };
/// @brief
/// @tparam NodePtr 被约束，必须要有left。和right
/// @tparam Func
/// @tparam ...Args
/// @param head 根节点
/// @param func 回调函数
/// @param ...args
/// 参数包，注意第一个参数是遍历二叉树遍历到的当前节点，如果要返回值，第二个参数传引用
template <NodePtrAble NodePtr, class Func, class... Args>
void foreach_front(NodePtr head, Func func, Args &&...args) {
  _SPC stack<NodePtr> sk;
  NodePtr temp = head;
  while (!sk.empty() || temp != nullptr) {
    while (temp != nullptr) {
      func(temp, std::forward<Args>(args)...);
      // re.push_back(temp); // 相当于printf
      sk.push(temp);
      temp = temp->left;
    }
    if (!sk.empty()) {
      temp = sk.top();
      sk.pop(); // 去掉中间节点
      temp = temp->right;
    }
  }
}
template <NodePtrAble NodePtr, class Func, class... Args>
void foreach_mid(NodePtr head, Func func, Args &&...args) {
  _SPC stack<NodePtr> sk;
  NodePtr temp = head;
  while (!sk.empty() || temp != nullptr) {
    while (temp != nullptr) {
      sk.push(temp);
      temp = temp->left;
    }
    if (!sk.empty()) {
      temp = sk.top();
      // re.push_back(temp); // 相当于printf
      func(temp, std::forward<Args>(args)...);
      sk.pop(); // 去掉中间节点
      temp = temp->right;
    }
  }
}
// 后序遍历 如果取出的上一个节点是栈顶的right，就可以取出栈顶
// 如果不是 就进入右子树
template <NodePtrAble NodePtr, class Func, class... Args>
void foreach_back(NodePtr head, Func func, Args &&...args) {
  _SPC stack<NodePtr> sk;
  NodePtr temp = head;
  NodePtr last = head;
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
    func(temp, std::forward<Args>(args)...);
    temp = nullptr; // 避免重复访问左子节点
    sk.pop();
  }
}

//_修正节点横坐标
template <class T> void update_row(Node<T> *head) {
  int row = 0;
  ::foreach_mid(head, [](Node<T> *cur,int& _row){
    cur->row = _row++;
  },row);
}
//_修正节点纵坐标
template <class T> void update_col(Node<T> *head) {
  if (head == nullptr)
    return;
  _SPC queue<Node<T> *> qe;
  qe.push(head);
  qe.push(nullptr);
  int index = 0;
  do {
    Node<T> *node = qe.front();
    qe.pop();
    if (node!=nullptr) {
      node->col = index;
      // cout << node->val << " ";
      if (node->left)
        qe.push(node->left);
      if (node->right)
        qe.push(node->right);
    } else if (!qe.empty()) {
      qe.push(nullptr);
      ++index;
    }
  } while (!qe.empty());
}
// 修正坐标
template <class T> void update_xy(Node<T> *head) {
  update_row(head);
  update_col(head);
}

#endif