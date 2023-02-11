#ifndef WIDGET_Hqq
#define WIDGET_Hqq


#include <QWidget>
class QGraphicsScene;
class testWin : public QWidget {
  Q_OBJECT
public:
  testWin(QWidget *parent = nullptr);
  ~testWin() {}
  void test1();
  void test2();
  // public Q_SLOTS:

private:
  int a = 0;
  QGraphicsScene * scene;
};
#endif // WIDGET_H
