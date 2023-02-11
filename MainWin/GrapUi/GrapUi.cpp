#include "GrapUi.h"
#include <QFontDatabase>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPixmap>

namespace {
QString OrderQStr(const EechOrder &order) {
  QString str;
  switch (order) {
  case EechOrder::先序:
    str = "先序";
    break;
  case EechOrder::中序:
    str = "中序";
    break;
  case EechOrder::后序:
    str = "后序";
    break;
  case EechOrder::层级:
    str = "层级";
    break;
  case EechOrder::选择:
    str = "选择";
    break;
  default:
    break;
  }
  return QString("%1遍历").arg(str);
}

} // namespace
// UiForeachBtn::UiForeachBtn(QGraphicsItem *parent) {
//   pix.load(":m/res/img/遍历完整加明.png");
//   pix.scaledToHeight(40);
//   // 下拉列表的根btn
//   writeArea =
//       QRectF(QPointF(-pix.width() / 2.0 + 40, -pix.height() / 2.0),
//       pix.size());
//   this->order = EechOrder::选择;

//   int fontId =
//   QFontDatabase::addApplicationFont(":/p/res/font/XiaoKeNa.ttf"); QString
//   fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
//   font.setFamily(fontFamily);
//   font.setPointSize(50);
// }
UiForeachBtn::UiForeachBtn(EechOrder order) {

  pix.load(":m/res/img/遍历空-明.png");
  pix = pix.scaledToHeight(25);
  writeArea = QRectF(QPointF(0, 5), pix.size());
  this->order = order;
  int fontId = QFontDatabase::addApplicationFont(":/p/res/font/XiaoKeNa.ttf");
  QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
  font.setFamily(fontFamily);
  font.setPointSize(10);
}
void UiForeachBtn::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget) {
  // painter->drawPixmap(boundingRect().topLeft(), pix);
  painter->drawPixmap(0, 0, pix);
  painter->setFont(font);
  auto tl = writeArea.bottomLeft();

  painter->drawText(writeArea, Qt::AlignHCenter, OrderQStr(order));
}

QRectF UiForeachBtn::boundingRect() const {
  // return QRectF(QPointF(-pix.width() / 2.0, -pix.height() / 2.0),
  // pix.size());
  return QRectF(QPointF(), pix.size());
}
void UiForeachBtn::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {

  if (event->button() == Qt::LeftButton) {
    qDebug() << "左键双击";
    // QPointF pos = this->mapToScene(boundingRect().bottomRight());
    emit ChildBtnPress(this->order);
  }
}
void UiForeachBtn::hide_() {
  this->hide();
  this->scene()->update();
}
/*------------------------------------------------------------
--------------------------------------------------------------
--------------------------------------------------------------
*/
UiForeachRootBtn::UiForeachRootBtn() {
  // 下拉列表的根btn
  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemIsSelectable);
  // 遍历完整加明
  pix.load(":m/res/img/遍历完整加暗.png");
  pix = pix.scaledToHeight(30);
  writeArea = QRectF(QPointF(20, 5), pix.size());
  this->order = EechOrder::选择;
  int fontId = QFontDatabase::addApplicationFont(":/p/res/font/XiaoKeNa.ttf");
  QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
  font.setFamily(fontFamily);
  font.setPointSize(15);
}
void UiForeachRootBtn::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {

  if (event->button() == Qt::LeftButton) {
    qDebug() << "左键双击";
    // QPointF pos = this->mapToScene(boundingRect().bottomRight());
    emit RootBtnPress(this);
  }
}
bool UiForeachRootBtn::IsOpen() { return isOpen; }
void UiForeachRootBtn::set_IsOpen(bool flag) { this->isOpen = flag; }
void UiForeachRootBtn::set_order(EechOrder order) {
  this->order = order;
  this->scene()->update();
}

/*------------------------------------------------------------
--------------------------------------------------------------
--------------------------------------------------------------
*/

UiBuildClearBtn::UiBuildClearBtn() : QObject(nullptr), QGraphicsItem(nullptr) {}
