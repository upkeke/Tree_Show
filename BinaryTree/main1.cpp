
#include<BinaryTree.hpp>
#include<some_func.h>
#include<MyTree.hpp>

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
   auto arr = h1.foreach_mid();
  // auto arr = h1.foreach_back();
  // auto arr = h1.foreach_ceng();
  //auto arr = h1.get_leaves();
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
  // MyTree<HHHx> k{&x};
}
void test4() {
  MyTree<Node<int>> h1{};
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
int main(int argc, char *argv[]) {
  test2();
  return 0;
}