
#include "FuncForTreeStr.h"
#include "NodeStr.hpp"
namespace sbt {

QPointF operator*(const PosStrNode &ps, const QPointF &pt) {
  return QPointF(ps.row * pt.x(), ps.col * pt.y());
}
QPointF operator*(const QPointF &pt, const PosStrNode &ps) { return ps * pt; }
//_修正节点横坐标
void update_row(NodePtr head, int scale_row) {
  int row = 0;
  sbt::foreach_mid(
      head, [](NodePtr cur, int &_row, int s) { cur->row = _row++ * s; }, row,
      scale_row);
}
//_修正节点纵坐标
void update_col(NodePtr head, int scale_col) {
  if (head == nullptr)
    return;
  _SPC queue<NodePtr> qe;
  qe.push(head);
  qe.push(nullptr);
  int index = 0;
  do {
    NodePtr node = qe.front();
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
void update_xy(NodePtr head, int scale_row, int scale_col) {
  if (head == nullptr)
    return;
  update_row(head, scale_row);
  update_col(head, scale_col);
}
} // namespace sbt
