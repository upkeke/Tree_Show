#include "HeadNode.h"
namespace sbt {

// 调试用
NodePtr create_tree() {
  // vector<int> data = get_vector_norepeat(10);
  _SPC vector<QString> data(7);
  for (int i = 0; i < 7; ++i) {
    data[i] = QString::number(i);
  }
  NodePtr head = new Node(data[0]);
  _SPC queue<NodePtr> qe;
  qe.push(head);
  size_t i = 1;
  while (!qe.empty()) {
    if (i == data.size())
      break;
    NodePtr temp = qe.front();
    temp->left = new Node(data[i++]);
    qe.push(temp->left);
    if (i == data.size())
      break;
    temp->right = new Node(data[i++]);
    qe.push(temp->right);
    qe.pop();
  }
  sbt::update_xy(head);
  return head;
}

_SPC vector<NodePtr> foreach_front_v(NodePtr head) {
  _SPC vector<NodePtr> re;
  sbt::foreach_front(
      head, [](NodePtr cur, _SPC vector<NodePtr> &_re) { _re.push_back(cur); },
      re);
  return re;
}

_SPC vector<NodePtr> foreach_mid_v(NodePtr head) {
  _SPC vector<NodePtr> re;

  sbt::foreach_mid(
      head, [](NodePtr cur, _SPC vector<NodePtr> &_re) { _re.push_back(cur); },
      re);
  return re;
}
_SPC vector<NodePtr> foreach_back_v(NodePtr head) {
  _SPC vector<NodePtr> re;
  sbt::foreach_back(
      head, [](NodePtr cur, _SPC vector<NodePtr> &_re) { _re.push_back(cur); },
      re);
  return re;
}
_SPC vector<NodePtr> foreach_ceng_v(NodePtr head) {

  _SPC vector<NodePtr> re;
  _SPC queue<NodePtr> qe;
  qe.push(head);
  while (!qe.empty()) {
    NodePtr temp = qe.front();
    re.push_back(temp);
    if (temp->left != nullptr)
      // qe.push(temp->left);
      qe.push(temp->left);
    if (temp->right != nullptr)
      // qe.push(temp->right);
      qe.push(temp->right);
    qe.pop();
  }
  return re;
}

_SPC vector<NodePtr> get_leaves_v(NodePtr head) {
  _SPC vector<NodePtr> re;
  sbt::foreach_front(
      head,
      [](NodePtr cur, _SPC vector<NodePtr> &_re) {
        if (cur->left == nullptr && cur->right == nullptr) {
          _re.push_back(cur);
        }
      },
      re);
  return re;
}

void insert_node(NodePtr derived, NodePtr base, bool isLeft) {

  if (isLeft) {
    base->left = derived;
  } else {
    base->right = derived;
  }
  sbt::update_col(derived, base->col + 1);
  derived->color = base->color;
  // 无法修正row
}
void delete_tree(NodePtr head) {
  sbt::foreach_back(head, [](NodePtr cur) { delete cur; });
}
} // namespace sbt
