
#include <BinaryTree.hpp>
#include <QDebug>
#include <TreeHead.hpp>
#include <iostream>
#include <common_func.hpp>
#include <data_source.h>
void test1() {
  TreeHead<Node<int>> h1{};

  h1.create_tree();
  auto arr = h1.foreach_front();
  for (auto item : arr) {
    std::cout << item->val << '\t';
  }
  std::cout << "\n++++++++++++++++++\n";
  TreeHead h2(h1);
  auto arr1 = h2.foreach_front();
  for (auto item : arr1) {
    std::cout << item->val << '\t';
  }
}
void test2() {
  TreeHead<Node<int>> h1{};
  h1.create_tree();
  auto arr = h1.foreach_mid();
  // auto arr = h1.foreach_back();
  // auto arr = h1.foreach_ceng();
  // auto arr = h1.get_leaves();
  for (auto item : arr) {
    std::cout << item->val << '\t';
  }
}
struct HHHx : Node<int> {
  int cval;
  /* data */
};

void test3() {
  HHHx x{};
  x.val = 10;
  // cout<< xxx1(&x);
  // decltype(x.left); //
  update_col(&x);
  // TreeHead<HHHx> k{&x};
}
void test4() {
  TreeHead<Node<int>> h1{};
  h1.create_tree();
  vector<Node<int> *> get;
  using NodePtr = Node<int> *;
  std::function<void(NodePtr, vector<NodePtr> &)> func =
      [](NodePtr tp, vector<NodePtr> &want) { want.push_back(tp); };

  foreach_front(h1.head, func, get);

  for (auto item : get) {
    std::cout << item->val << '\t';
  }
}
struct xxx {
  int x = 10;
};
void test7(int &&) { ; }
void test7(int &) { ; }
void test8() {
  auto arr = get_vector<QString>(12);
  for (auto xx : arr) {
    qDebug() << xx;
  }
}
void test9() {
  // HHHx x{};
  // qDebug() << val_to_qstring(x);
  int x1 = 10;
  constexpr bool f = std::is_arithmetic_v<int>;
  constexpr bool f1 = std::is_object_v<int>;
  qDebug() << val_to_qstring<int>(x1);
}
struct xxx0 {
  int x = 10;
};
struct xxx11 {
  int x = 10;
  operator QString() const { return QString::number(x); }
};
void test10() {
  // xxx0 x0{123};
  // qDebug() << val_to_qstring(x0);
  xxx11 x1{45};
  qDebug() << val_to_qstring(x1);
  double x2 = 12.3545;
  qDebug() << val_to_qstring(x2);
  int x3 = 36;
  qDebug() << val_to_qstring(x3);
  char x4 = 'k';
  qDebug() << val_to_qstring(x4);
  bool x5 = false;
  qDebug() << val_to_qstring(x5);
  QString x6 = "nnnn";
  qDebug() << val_to_qstring(x6);
  unsigned char x7 = 'k';
  qDebug() << val_to_qstring(x7);
  // std::is_integral_v<char>;
  constexpr bool f1 = std::is_same_v<char, unsigned char>;
  constexpr bool f11 = std::common_with<char, unsigned char>;
  constexpr bool f12 = std::common_with<char, signed char>;
  constexpr bool f2 = std::signed_integral<char>;
  // common_with
}
int main(int argc, char *argv[]) {
  test10();
  return 0;
}