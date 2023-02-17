
#include "FuncForHeadNode.h"

namespace sbt {

QPointF operator*(const PosStrNode &ps, const QPointF &pt) {
  return QPointF(ps.row * pt.x(), ps.col * pt.y());
}
QPointF operator*(const QPointF &pt, const PosStrNode &ps) { return ps * pt; }
//_修正节点横坐标
void update_row(NodePtr head) {
  int row = 0;
  sbt::foreach_mid(
      head, [](NodePtr cur, int &_row) { cur->row = _row++; }, row);
}
//_修正节点横坐标
void update_row(NodePtr head, const QPointF &offset) {
  int row = 0;
  sbt::foreach_mid(
      head,
      [](NodePtr cur, int &_row, const QPointF &_offset) {
        cur->row = _row++;
        cur->toScenePos(_offset);
      },
      row, offset);
}
//_修正节点纵坐标
void update_col(NodePtr head, const QPointF &offset) {
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
      node->col = index;
      node->toScenePos(offset);
      // cout << node->val << " ";
      if (node->left)
        qe.push(node->left);
      if (node->right)
        qe.push(node->right);
    } else if (!qe.empty()) {
      qe.push(nullptr);
      ++index;
    }
  } while (!qe.empty());
}

// 修正坐标
void update_xy(NodePtr head, const QPointF &offset) {
  if (head == nullptr)
    return;
  update_row(head);
  // 这一步不仅要更新col，还要更新节点在场景的坐标，也就是成员变量pos
  update_col(head, offset);
}
} // namespace sbt
