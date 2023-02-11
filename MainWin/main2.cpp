#include <get_test_data.h>

struct Node1 : _baseNode<char> {
  using _baseNode<char>::_baseNode;
};
Node1 *creatNode1() {
  auto data = get_vector<char>(3);
  Node1 *head = new Node1(data[0]);
  _SPC queue<_baseNode<char> *> qe;
  qe.push(head);
  size_t i = 1;
  while (!qe.empty()) {
    if (i == data.size())
      break;
    _baseNode<char> *temp = qe.front();
    temp->left = new Node1(data[i++]);
    qe.push(temp->left);
    if (i == data.size())
      break;
    temp->right = new Node1(data[i++]);
    qe.push(temp->right);
    qe.pop();
  }
  return head;
}

struct Node2 {
  char val;
  Node2 *left = nullptr;
  Node2 *right = nullptr;
  Node2(char val) : val(val) {}
};
Node2 *creatNode2() {
  auto data = get_vector<char>(3);
  Node2 *head = new Node2(data[0]);
  _SPC queue<Node2 *> qe;
  qe.push(head);
  size_t i = 1;
  while (!qe.empty()) {
    if (i == data.size())
      break;
    Node2 *temp = qe.front();
    temp->left = new Node2(data[i++]);
    qe.push(temp->left);
    if (i == data.size())
      break;
    temp->right = new Node2(data[i++]);
    qe.push(temp->right);
    qe.pop();
  }
  return head;
}
#include <iostream>
void func1() {
  auto data = get_vector<int>(3);
  for (auto i : data) {
    std::cout << i << '\t';
  }
}
#include "widget.h"
#include <QApplication>

int main1(int argc, char *argv[]) {
  QApplication a(argc, argv);
  testWin w;
  w.show();
  return a.exec();
}
int main() {
  // auto p = creatNode1();
  // std::cout<<p->val;
  func1();
  return 0;
}