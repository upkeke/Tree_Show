#include "GrapItemManager.h"
#include "GrapLineItem.h"
#include "GrapNodeItem.h"
#include <FuncForHeadNode.h>
#include <HeadNode.h>
#include <QGraphicsScene>

using namespace sbt;
GrapItemManager::GrapItemManager(QGraphicsScene *scene,
                                 std::unordered_set<sbt::NodePtr> &trees,
                                 sbt::NodePtr &curtree)
    : scene(scene), trees(trees), curtree(curtree) {

  GrapNodeItem::init_static_mem(this);
}

std::shared_ptr<GrapItemManager>
GrapItemManager::instance(QGraphicsScene *scene,
                          std::unordered_set<sbt::NodePtr> &trees,
                          sbt::NodePtr &curtree) {
  if (ItemManager == nullptr) {
    ItemManager = std::shared_ptr<GrapItemManager>(
        new GrapItemManager(scene, trees, curtree));
  }
  return ItemManager;
}
QGraphicsScene *GrapItemManager::getScene() { return scene; }
/**
 * @brief
 *
 三种情况
 1，外界构造好node ，传来一个nodeptr竟来只用
 1.1 如果有剩余的GrapNodeItem，直接reset它的nodptr
 1.2，没有剩余的GrapNodeItem，需要new一个GrapNodeItem

 2 外界传入构造node的参数，内部有剩余的GrapNodeItem，里面的node也还保留，
 * @param nodeptr
 * @param isNew
 * @return GrapNodeItem*
 */
GrapNodeItem *GrapItemManager::getGrapNode(sbt::NodePtr nodeptr, bool &isNew,
                                           sbt::NodePtr headptr) {
  GrapNodeItem *item = nullptr;
  if (freeNodePool.empty()) {
    item = new GrapNodeItem(nodeptr, headptr);
    nodeToGrapNode[nodeptr] = item;
    scene->addItem(item);
    isNew = true;
  } else {
    item = freeNodePool.top();
    freeNodePool.pop();
    item->reSet(nodeptr, headptr);
    isNew = false;
  }

  item->show();
  return item;
}

void GrapItemManager::mergeTree(GrapNodeItem *main_item,
                                GrapNodeItem *sub_item) {
  trees.erase(sub_item->getNodePtr());

  auto base_node = main_item->getNodePtr();
  auto new_node = sub_item->getNodePtr();
  // 如果base_node可插入
  if (base_node->left == nullptr || base_node->right == nullptr) {
    bool isLeft = true;
    // 左子树可插入且插入节点的位置位于根节点的左边
    // 可能存在一种情况，base_item的左子树不为空，右子树为空，能进入这儿
    // 但是如果当前节点是在base_item的左边，那么不能连接二者，直接return
    if (sub_item->pos().x() <= main_item->pos().x()) {
      auto bs_tp = base_node->left;
      if (bs_tp == nullptr) {
        ;
      } else {
        return;
      }
    } else {
      auto bs_tp = base_node->right;
      if (bs_tp == nullptr) {
        isLeft = false;
      } else {
        return;
      }
    }
    sbt::insert_node(new_node, base_node, isLeft);
    qDebug() << "我碰到了可插入节点" << main_item->strVal();
    //  插入后，将它和它的子图元的设置重设父节点
    this->reSetTreeNodeItemHead(sub_item, main_item->getHeadPtr());
    this->getGrapLine(main_item, sub_item, isLeft);
  }
}
void GrapItemManager::ShowDepthOrVal(bool flag) {
  auto items = scene->items();
  for (auto item : items) {
    auto x = qgraphicsitem_cast<GrapNodeItem *>(item);
    if (x != nullptr) {
      x->SetIsShowDepth(flag);
    }
  }
}
GrapNodeItem *GrapItemManager::whereGrapNode(NodePtr nodeptr) {
  if (nodeToGrapNode.contains(nodeptr)) {
    return nodeToGrapNode[nodeptr];
  }
  return nullptr;
}

void GrapItemManager::reSetTreeNodeItemHead(GrapNodeItem *treeItem,
                                            NodePtr headPtr) {
  treeItem->setHeadPtr(headPtr);
  sbt::foreach_front(
      headPtr,
      [headPtr](NodePtr cur, unordered_map<sbt::NodePtr, GrapNodeItem *> &mp) {
        if (mp.contains(cur)) {
          mp[cur]->setHeadPtr(headPtr);
        }
      },
      this->nodeToGrapNode);
}
/**
 * @brief
 由于可能添加了子节点，添加子节点只能顺带修正col，不能修正row
 因此这儿需要修正row，同时添加偏移量
 *
 * @param head
 * @param offset
 */
void GrapItemManager::updateGrapNodePos(sbt::NodePtr head) {
  QPointF offset = head->getOffsetByNowPos();
  qDebug() << "刷新节点位置 头节点是 " << head->val;
  qDebug() << "偏移值是 " << offset;
  int row = 0;
  sbt::foreach_mid(
      head,
      [](NodePtr cur, const QPointF &_offset,
         unordered_map<sbt::NodePtr, GrapNodeItem *> &_nodeToGrapNode,
         int &_row) {
        cur->row = _row++;
        cur->toScenePos(_offset);
        _nodeToGrapNode[cur]->setPos(cur->Pos());
      },
      offset, nodeToGrapNode, row);
}
void GrapItemManager::LineNodeToChild(GrapNodeItem *fatherItem) {
  auto fatherNode = fatherItem->getNodePtr();
  for (size_t j = 0; j < 2; ++j) {
    NodePtr childNode = nullptr;
    if (j == 0)
      childNode = fatherNode->left;
    else
      childNode = fatherNode->right;
    if (childNode != nullptr) {
      // 后序遍历，子节点图元必然先于父节点创建，可以不判断nodeToGrapNode[childNode]
      auto childItem = nodeToGrapNode[childNode];
      GrapLineItem *curLineItem = getGrapLine(fatherItem, childItem, j == 0);
    }
  }
}
GrapLineItem *GrapItemManager::getGrapLine(GrapNodeItem *front,
                                           GrapNodeItem *end, bool isleft) {
  GrapLineItem *re = nullptr; // getGrapLine(front, end);
  if (!freeLinePool.empty()) {
    re = freeLinePool.top();
    freeLinePool.pop();
    re->setTwo(front, end, isleft);
  } else {
    re = new GrapLineItem(front, end, isleft);
    scene->addItem(re);
  }
  re->show();
  return re;
}
void GrapItemManager::removeLine(GrapLineItem *line) {
  line->hide();
  freeLinePool.push(line);
}
void GrapItemManager::removeLine(GrapNodeItem *father, GrapNodeItem *child) {

  auto fatherPtr = father->getNodePtr();
  auto childPtr = child->getNodePtr();
  // 将父节点和自己断开
  if (fatherPtr != nullptr) {
    qDebug() << "父节点是 " << fatherPtr->val;
    bool isLeft = (fatherPtr->left == childPtr);
    if (isLeft) {
      fatherPtr->left = nullptr;
    } else {
      fatherPtr->right = nullptr;
    }
    auto line = father->rmoveLine(isLeft);
    child->setFatherItem(nullptr);
    this->removeLine(line);
  }
}
void GrapItemManager::disconnectGrapNode(GrapNodeItem *father,
                                         GrapNodeItem *child) {
  removeLine(father, child); // 更新所有子树图元的根节点
  auto childPtr = child->getNodePtr();
  this->reSetTreeNodeItemHead(child, childPtr);
  sbt::update_col(childPtr);
}
GrapItemManager::~GrapItemManager() {}
/*------------------------------------------------------------
--------------------------------------------------------------
slots  slots  slots  slots  slots  slots  slots  slots  slots
--------------------------------------------------------------
--------------------------------------------------------------
*/

void GrapItemManager::set_main_tree(GrapNodeItem *tree) {
  curtree = tree->nodePtr;
  curtree->color = sbt::NodeColor::magenta;
  scene->update();
}
void GrapItemManager::truncate_tree(GrapNodeItem *curItem) {
  this->disconnectGrapNode(curItem->getFatherItem(), curItem);
  // 加入到集合中
  trees.insert(curItem->getNodePtr());
  scene->update();
}
#include <QInputDialog>
#include <QLineEdit>
void GrapItemManager::changeNodeVal(GrapNodeItem *curitem) {
  auto node = curitem->getNodePtr();
  bool ok;
  QString text = QInputDialog::getText(static_cast<QWidget *>(scene->parent()),
                                       tr("Enter text"), tr("Text:"),
                                       QLineEdit::Normal, QString(), &ok);
  if (ok && !text.isEmpty()) {
    node->val = text;
  }
  scene->update();
}
// delete
void GrapItemManager::deleteTree(GrapNodeItem *headGrapItem) {
  if (headGrapItem->isHeadItem())
    trees.erase(headGrapItem->getNodePtr());
  else
    this->removeLine(headGrapItem->getFatherItem(), headGrapItem);
  sbt::foreach_back(
      headGrapItem->getNodePtr(),
      [](NodePtr cur, GrapItemManager *self) {
        auto item = self->nodeToGrapNode[cur];
        item->hide();
        self->freeNodePool.push(item);
        auto lines = item->reMoveLines();
        // 将直线还给管理器
        for (auto i : lines) {
          if (i != nullptr) {
            i->hide();
            self->freeLinePool.push(i);
          }
        }
        delete cur;
      },
      this);
  scene->update();
}