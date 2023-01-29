
#include "BinaryTree.hpp"
#include "some_func.h"
#include <MyTree.hpp>
#include <iostream>
using std::cout;

void test1() {
  MyTree<Node<int>> h1{};

  h1.create_tree();
  auto arr = h1.foreach_front();
  for (auto item : arr) {
    std::cout << item->val << '\t';
  }
  std::cout << "\n++++++++++++++++++\n";
  MyTree h2(h1);
  auto arr1 = h2.foreach_front();
  for (auto item : arr1) {
    std::cout << item->val << '\t';
  }
}
void test2() {
  MyTree<Node<int>> h1{};
  h1.create_tree();
  // auto arr = h1.foreach_mid();
  // auto arr = h1.foreach_back();
  // auto arr = h1.foreach_ceng();
  auto arr = h1.get_leaves();
  for (auto item : arr) {
    std::cout << item->val << '\t';
  }
}
struct HHHx :Node<int>{
  int cval;
  /* data */
};

void test3() {
  HHHx x{};
  x.val = 10;
  //cout<< xxx1(&x);
  //decltype(x.left); //
  update_col(&x);
  //MyTree<HHHx> k{&x};
}

int main(int argc, char *argv[]) {
  test3();
  return 0;
}