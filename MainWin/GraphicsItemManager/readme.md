# GrapUi
这一部分是UI图元，和动画有联系
这部分我也不知道该把它放在那个位置，它不归GrapItemManager管理，它的析构也不是归GrapItemManager管理，不会产生动画的由mainwin或者后面会有一个

![x1](E:\code\23-a\Tree_Show\MainWin\GraphicsItemManager\res\img\遍历完整.png)

```c
 connect(a2, &QAction::triggered, [this]() {
    if (isHeadItem())
      return;
    NodePtr father = nullptr;
    bool isleft = false;
    for (auto line : lineArry) {
      auto [first, end] = line->getFrontEnd();
      GrapNodeItem *want = first;
      if (first == this) {
        want = end;
      }
      if (want->nodePtr->left == nodePtr) {
        line->hide();
        father = want->nodePtr;
        isleft = true;
        break;
      }
      if (want->nodePtr->right == nodePtr) {
        line->hide();
        father = want->nodePtr;
        break;
      }
    }
    if (father != nullptr) {
      qDebug() << "父节点是 " << father->val;
      actionOnlyHead();
      // menu->addActions(const QList<QAction *> &actions)
      if (isleft) {
        father->left = nullptr;
      } else {
        father->right = nullptr;
      }
      this->scene()->update();
      // this->isHead = true;
      emit truncateCurTree(this);
    }




```