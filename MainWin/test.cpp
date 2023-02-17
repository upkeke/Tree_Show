
#include <QGraphicsItem>
class X1 : public QGraphicsItem {
public:
  enum { Type = UserType + 1 };
  int type() const override { return Type; }
  QRectF boundingRect() const override { return QRectF(0, 0, 1, 1); }
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr) override {}
};

class X2 : public QGraphicsItem {
public:
  enum { Type = UserType + 2 };
  int type() const override { return Type; }
  QRectF boundingRect() const override { return QRectF(0, 0, 1, 1); }
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr) override {}
};
namespace xx {

template <class T> inline T qgraphicsitem_cast(QGraphicsItem *item) {
  typedef
      typename std::remove_cv<typename std::remove_pointer<T>::type>::type Item;
  return int(Item::Type) == int(QGraphicsItem::Type) ||
                 (item && int(Item::Type) == item->type())
             ? static_cast<T>(item)
             : nullptr;
}
} // namespace xx
#include <QGraphicsItemGroup>
#include <iostream>
#include <QGraphicsScene>
void func1() {
  QGraphicsItemGroup *gp = new QGraphicsItemGroup();
  X2 *x = new X2();
  gp->addToGroup(x);
  QGraphicsScene sc;
  sc.addItem(x);
  std::cout << (x->parentItem() == gp)<<'\n';
  //std::cout << (x->parentItem() == &sc)<<'\n';
}
#include <unordered_map>
void func2() {
  
}
int main(int argc, char *argv[]) {
  func1();
  return 0;
}