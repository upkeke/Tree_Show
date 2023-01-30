// author : keke
// date : 2023/01/27
#pragma once
#ifndef __SOME_FUNC__
#define __SOME_FUNC__

#include <BinaryTree.hpp>
#include <CXX_STD.h>
#include <QSql>
#include <QSqlDatabase> //用来连接和打开数据库
#include <QSqlError>
#include <QSqlQuery> //用来访问和操作数据库
#include <QString>

#include <algorithm>
#include <concepts>
#include <numeric>
#include <queue>
#include <random>
#include <stack>
#include <string>
#include <vector>

using std::stack;
using std::string;
using std::vector;
// 打乱数组
template <class T> void shuffle_vector(vector<T> &arr) {
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(arr.begin(), arr.end(), g);
}
// template <>
// vector<int> get_vector_norepeat<int>(size_t sz, int _min = 0, int _max =
// 100); template <class T> vector<int> get_vector_order(int _min, int _max);

template <class T> vector<T> get_vector(size_t sz) { return {}; }
template <> inline vector<QString> get_vector<QString>(size_t sz) {
  if (sz > 50)
    return {};
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("somedata.db");
  QSqlQuery query;
  if (!db.open()) {
    return {};
  }
  QString order =
      QString("select * from string order by random() limit %1;").arg(sz);
  if (!query.exec(order)) {
    return {};
  }
  vector<QString> arr(sz);
  size_t i = 0;
  while (query.next() && i < sz) {
    arr[i++] = query.value("name").toString();
  }
  return arr;
}
vector<int> get_vector_norepeat(size_t sz, int _min = 0, int _max = 100);
vector<int> get_vector_order(int _min, int _max);

// template <class T>
// concept str_able = true;
#if 0
template <class T>
  requires std::is_arithmetic_v<T>
QString val_to_qstring(const T &val) {
  return QString::number(val);
}
template <class T>
  requires(!std::is_fundamental_v<T>)
QString val_to_qstring(const T &val) {
  return "hhhh";
}
template <class T>
  requires std::is_convertible_v<T, QString>
QString val_to_qstring(const T &val) {
  return val;
}
template <> inline QString val_to_qstring<char>(const char &val) {
  return QString(1, val);
}
template <> inline QString val_to_qstring<bool>(const bool &val) {
  return val ? "true" : "false";
}
#endif
// template <class T>
// concept qstr_able =
//     std::is_arithmetic_v<T> || std::is_convertible_v<T, QString>;

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
  stack<NodePtr> sk;
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
  stack<NodePtr> sk;
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
  stack<NodePtr> sk;
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
  std::queue<Node<T> *> qe;
  qe.push(head);
  qe.push(0);
  int index = 0;
  do {
    Node<T> *node = qe.front();
    qe.pop();
    if (node) {
      node->col = index;
      // cout << node->val << " ";
      if (node->left)
        qe.push(node->left);
      if (node->right)
        qe.push(node->right);
    } else if (!qe.empty()) {
      qe.push(0);
      ++index;
    }
  } while (!qe.empty());
}

template <class T> void update_xy(Node<T> *head) {
  int index = 0;
  update_row(head, index);
  update_col(head);
}
template <class T>
void _后序遍历收集节点(Node<T> *head, vector<Node<T> *> &vt) {
  if (head == nullptr)
    return;
  _后序遍历收集节点(head->left, vt);
  _后序遍历收集节点(head->right, vt);
  vt.push_back(head);
}
template <class T> vector<Node<T> *> w节点集合(Node<T> *head) {
  // 这一步会修正所有节点的坐标，
  update_xy(head);
  vector<Node<T> *> vt; // 按后序遍历 收集每一个节点
  _后序遍历收集节点(head, vt);
  return vt;
}

#if CXX_STD >= CXX20
struct AA {
  int left;
  char right;
  double val;
};
template <class T>
concept able1 =
    requires(T obj) {
      obj.left;
      obj.right;
      obj.val;
      requires(std::same_as<decltype(obj.left), decltype(obj.right)>);
      { *obj.left } -> std::convertible_to<T>;
    };

#endif
#endif