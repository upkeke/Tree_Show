#include "mainwin.h"
#include <QApplication>
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
    _baseNode<char> * temp = qe.front();
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
  Node2 *left =nullptr;
  Node2 *right =nullptr;
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
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  //_baseNode<int > nd (10);
  MainWin w;
  //传入树节点的根节点。如果不传入会生成默认的二叉树
  w.set_node_head(creatNode2());
  w.show();
  return a.exec();
}
