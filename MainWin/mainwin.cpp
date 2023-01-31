#include "mainwin.h"
#include "ui_mainwin.h"
//#include "uui_mainwin.h"

#include "MyGraphicsItem.h"
#include "MyLineItem.h"
#include <common_func.hpp>
#include <QGraphicsPixmapItem>

MainWin::MainWin(QWidget *parent) : QWidget(parent), ui(new Ui::mainwin) {
  ui->setupUi(this);
  tree = new TreeHead<Node<int>>();
  tree->create_tree();
  scene = new QGraphicsScene(this);
  //:/m/img/green.jpg
  QGraphicsPixmapItem *item2 = new  QGraphicsPixmapItem(QPixmap(":/m/img/green.jpg"));
  //QGraphicsPixmapItem *item1 = new  QGraphicsPixmapItem( QPixmap(R"(:/img/green.jpg)"));


  //item2->setPos(100,100);

  ui->view->setScene(scene); // QGraphicsView
  //scene->addItem(item1);
  scene->addItem(item2);
  scene->update();


  connect(ui->btn_build, &QPushButton::clicked, this,
          &MainWin::btn_build_clicked);
}
MainWin::~MainWin() { delete ui; }

void MainWin::btn_build_clicked() { print_tree(tree->head); }
void MainWin::btn_foreach_clicked() {}

void MainWin::print_tree(NodePtr head) {
  //实际的节点个数
  vector<NodePtr> a节点集合 = node_back_list(head);
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
