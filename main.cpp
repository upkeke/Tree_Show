
#include "BinaryTree.hpp"
#include "some_func.h"
#include <MyTree.hpp>
#include <iostream>


void test1() {
  MyTree h1{};

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
  MyTree h1{};
  h1.create_tree();
  // auto arr = h1.foreach_mid();
  // auto arr = h1.foreach_back();
  // auto arr = h1.foreach_ceng();
  auto arr = h1.get_leaves();
  for (auto item : arr) {
    std::cout << item->val << '\t';
  }
}
#if CXX_STD>=CXX20
void test3() {
  MyTree h1{};

  h1.create_tree();
  Node<int>* ptr = h1.head;
  //<Node<int>> kn(ptr);
  KNlist kn1(ptr);
  auto arr = kn1.foreach_front();
  for (auto item : arr) {
    std::cout << item->val << '\t';
  }
  //AA a{10,'v',1.2};
  //KNlist k{&a};
  //k.show_val();

}
#include <format>
#endif


int main(int argc, char *argv[]) {
  test2();
  return 0;
}