#include "mainwin.h"
#include <QApplication>
#include <get_test_data.h>
struct Node1 : _baseNode<char> {
  using _baseNode<char>::_baseNode;
};
Node1 *creatNode1() {
  auto data = get_vector<char>(10);
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

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  //_baseNode<int > nd (10);
  MainWin w;
  w.set_node_head();
  w.show();
  return a.exec();
}
