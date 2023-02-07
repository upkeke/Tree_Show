
#include "FuncForTreeStr.h"
#include "BinaryTree.hpp"
QPointF operator*(const PosStrNode &ps, const QPointF &pt) {
  return QPointF(ps.row * pt.x(), ps.col * pt.y());
}
QPointF operator*(const QPointF &pt, const PosStrNode &ps) { return ps * pt; }
//_修正节点横坐标
void update_row(PosStrNode *head, int scale_row) {
  int row = 0;
  ::foreach_mid(
      head, [](PosStrNode *cur, int &_row, int s) { cur->row = _row++ * s; },
      row, scale_row);
}
//_修正节点纵坐标
void update_col(PosStrNode *head, int scale_col) {
  if (head == nullptr)
    return;
  _SPC queue<PosStrNode *> qe;
  qe.push(head);
  qe.push(nullptr);
  int index = 0;
  do {
    PosStrNode *node = qe.front();
    qe.pop();
    if (node != nullptr) {
      node->col = index * scale_col;
      // cout << node->val << " ";
      if (node->left)
        // qe.push(node->left);
        qe.push(node->Left());
      if (node->right)
        // qe.push(node->right);
        qe.push(node->Right());
    } else if (!qe.empty()) {
      qe.push(nullptr);
      ++index;
    }
  } while (!qe.empty());
}
// 修正坐标
void update_xy(PosStrNode *head, int scale_row, int scale_col) {
  if (head == nullptr)
    return;
  update_row(head, scale_row);
  update_col(head, scale_col);
}
