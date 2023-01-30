#include "mainwin.h"
#include "uui_mainwin.h"

#include "MyGraphicsItem.h"
#include "MyLineItem.h"
#include <some_func.h>



void _后序遍历收集节点(Node<int> *head, vector<Node<int> *> &vt) {
  if (head == nullptr)
    return;
  _后序遍历收集节点(head->left, vt);
  _后序遍历收集节点(head->right, vt);
  vt.push_back(head);
}
vector<Node<int> *> w节点集合(Node<int> *head) {
  // 这一步会修正所有节点的坐标，
  update_xy(head);
  vector<Node<int> *> vt; // 按后序遍历 收集每一个节点
  _后序遍历收集节点(head, vt);
  return vt;
}

MainWin::MainWin(QWidget *parent) : QWidget(parent), ui(new Ui::mainwin) {
  ui->setupUi(this);
  avl = new MyTree<Node<int>>();
  avl->create_tree();
  scene = new QGraphicsScene(this);

  ui->view->setScene(scene); // QGraphicsView
  connect(ui->btn_build, &QPushButton::clicked, this,
          &MainWin::btn_build_clicked);
}
MainWin::~MainWin() { delete ui; }

void MainWin::btn_build_clicked() {
  print_tree(avl->head);
}
void MainWin::btn_foreach_clicked() {}

void MainWin::print_tree(NodePtr head) {
  vector<NodePtr> a节点集合 = w节点集合(head);
  int s节点图元个数 = w节点图元池.size(); // 图元用完后不要丢
  int s节点个数 = a节点集合.size(); // 图元个数大于节点个数，隐藏多余的图元
  // 图元个数小于节点个数，添加调多余的图元
  int s直线图元个数 = w直线图元池.size();
  size_t myitem_i = 0; // 当前图元下标
  size_t line_i = 0;   // 当前直线图元下标
  for (; myitem_i < s节点个数; myitem_i++) {
    NodePtr ptr = a节点集合[myitem_i];

    int val = ptr->val;
    int x1 = ptr->row * 40;
    int y1 = ptr->col * 60; // 中心位置
    if (myitem_i < s节点图元个数) {

      w节点图元池[myitem_i]->setVal(val);
      w节点图元池[myitem_i]->setPos(QPointF(x1, y1));
      w节点图元池[myitem_i]->setBackColor(ptr->color);
    } else {
      MyGraphicsItem *item =
          new MyGraphicsItem(QPointF(x1, y1), val, ptr->color);
      w节点图元池.push_back(item);
      scene->addItem(item);
    }
    w节点图元池[myitem_i]->show();
    w节点图元池[myitem_i]->clearLines();
    // 连接父节点到子节点的线
    for (size_t j = 0; j < 2; ++j) {
      NodePtr child = nullptr;
      if (j == 0)
        child = ptr->left;
      else
        child = ptr->right;
      if (child != nullptr) {
        int x2 = child->row * 40;
        int y2 = child->col * 60;
        QTransform transform;
        auto point = w网格到坐标(child->row, child->col);
        // auto end = dynamic_cast<MyGraphicsItem*>(scene->itemAt(point,
        // transform));
        auto end = qgraphicsitem_cast<MyGraphicsItem *>(
            scene->itemAt(point, transform));
        if (line_i < s直线图元个数) // 调整图元位置
        {
          w直线图元池[line_i]->setTwo(w节点图元池[myitem_i], end);
        } else {
          MyLineItem *line = new MyLineItem(w节点图元池[myitem_i], end);
          w直线图元池.push_back(line);
          scene->addItem(line);
        }
        // 由于直线与2个图元连接，把直线添加到2个图元中
        w节点图元池[myitem_i]->addLine(w直线图元池[line_i]);
        end->addLine(w直线图元池[line_i]);
        w直线图元池[line_i]->show();
        line_i++;
      }
    }
  }
  for (size_t k = line_i; k < s直线图元个数; ++k) {
    w直线图元池[k]->hide();
  }
  // 图元池多出来的隐藏
  for (size_t k = myitem_i; k < s节点图元个数; k++) {
    w节点图元池[k]->hide();
  }
  scene->update();
  // ui->te_message->append("打印二叉树成功");
}
QPoint MainWin::w网格到坐标(int x, int y) { return QPoint(x * 40, y * 60); }
