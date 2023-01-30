// author : keke
// date : 2023/01/30
#pragma once
#ifndef __MAINWIN__
#define __MAINWIN__

#include <QWidget>
QT_BEGIN_NAMESPACE
namespace Ui {
class mainwin;
}
QT_END_NAMESPACE
#include <TreeHead.hpp>
#include <vector>

using std::vector;

class QGraphicsScene;
class QPoint;
class MyGraphicsItem;
class QGraphicsLineItem;
class MyLineItem;

// template <class T> struct Node;
// template <class T> struct MyTree;

class MainWin : public QWidget {
  Q_OBJECT
public:
  MainWin(QWidget *parent = nullptr);

  ~MainWin();

private:
  using NodePtr = Node<int> *;
  void print_tree(NodePtr head);
  QPoint w网格到坐标(int x, int y);
  Ui::mainwin *ui;
  TreeHead<Node<int>> *tree;

  QGraphicsScene *scene;
  vector<MyGraphicsItem *> w节点图元池;
  vector<MyLineItem *> w直线图元池;
private slots:
  void btn_build_clicked();
  void btn_foreach_clicked();
  // void btn_focus_next_clicked();
  // void btn_reverse_clicked();
};
#endif // WIDGET_H
