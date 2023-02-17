#include "ThScene.h"
#include <GrapNodeItem.h>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

/**/
ThScene::ThScene(QObject *parent) : QGraphicsScene(parent) {
  m_selectionRectItem = new QGraphicsRectItem();

  m_selectionRectItem->setPen(QPen(Qt::red, 1, Qt::DashLine));
  addItem(m_selectionRectItem);
}
void ThScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  QGraphicsScene::mousePressEvent(event);
  isItemSelected = selectedItems().size() != 0;
  if (!isItemSelected)
    if (event->button() == Qt::LeftButton) {
      // 记录按下位置
      m_selectionStart = event->scenePos();
      m_selectionRectItem->show();
    }
}

void ThScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  QGraphicsScene::mouseMoveEvent(event);
  if (!isItemSelected)
    if (event->buttons() & Qt::LeftButton) {
      m_selectionRectItem->setRect(QRectF(m_selectionStart, event->scenePos()));
    }
}

void ThScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
  QGraphicsScene::mouseReleaseEvent(event);
  if (!isItemSelected)
    if (event->button() == Qt::LeftButton) {
      // 计算选中区域矩形
      QRectF selectionRect(m_selectionStart, event->scenePos());
      // 选中碰撞的图元
      QList<QGraphicsItem *> items = this->items(selectionRect);
      qDebug() << "我选中的个数" << items.size();
      int cc = 0;
      for (QGraphicsItem *item : items) {
        auto *myItem = qgraphicsitem_cast<GrapNodeItem *>(item);
        if (myItem) {
          cc++;
          qDebug() << myItem->strVal();
          myItem->setSelected(true);
        }
      }
      m_selectionRectItem->setRect(0, 0, 0, 0);
      m_selectionRectItem->hide();
      qDebug() << "节点图元的个数 " << cc;
      this->update();
    }
}
