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
#include "GrapItemManager.h"
#include <BinaryTreeStr.hpp>
class QGraphicsScene;
class QPointF;
class GrapNodeItem;
class QGraphicsLineItem;
class GrapLineItem;
class QGraphicsItem;


class MainWin : public QWidget {
  Q_OBJECT
public:
  MainWin(QWidget *parent = nullptr);

  ~MainWin();

private:
  void print_tree(NodePtr head);
  Ui::mainwin *ui;
  BinaryTreeStr *tree;
  QGraphicsItem *ball;
  QGraphicsScene *scene;
  std::shared_ptr<GrapItemManager> grapPool;
private slots:
  void btn_build_clicked();
  void btn_foreach_clicked();
  // void btn_focus_next_clicked();
  void btn_reverse_clicked();
  void animate_foreach();
};

#endif // WIDGET_H
