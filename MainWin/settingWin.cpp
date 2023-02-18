
#include "settingWin.h"
// #include "buildtree.h"
#include <QDebug>

#include <QString>
#include <uix_settingWin.h>
#include <unordered_map>

namespace {
using namespace sbt;
using std::unordered_map;
NodePtr buildTreeByFrontMid(QStringList &preorder, QStringList &inorder,
                            unordered_map<QString, int> &index, int preLeft,
                            int preRight, int inLeft, int inRight) {
  if (preLeft > preRight) {
    return nullptr;
  }
  QString rootVal = preorder[preLeft]; // 前序遍历第一个节点是根节点
  int inRoot = index[rootVal]; // 找到根节点在中序遍历中的位置
  NodePtr root = new Node(rootVal);
  int leftSize = inRoot - inLeft; // 左子树节点个数
  root->left = buildTreeByFrontMid(preorder, inorder, index, preLeft + 1,
                                   preLeft + leftSize, inLeft,
                                   inRoot - 1); // 递归重建左子树
  root->right =
      buildTreeByFrontMid(preorder, inorder, index, preLeft + leftSize + 1,
                          preRight, inRoot + 1, inRight); // 递归重建右子树
  return root;
}
// 构建二叉树
NodePtr buildTree(QStringList &preorder, QStringList &inorder) {
  unordered_map<QString, int> index; // 哈希表记录中序遍历中每个节点值的下标
  for (int i = 0; i < inorder.size(); i++) {
    index[inorder[i]] = i;
  }
  return buildTreeByFrontMid(preorder, inorder, index, 0, preorder.size() - 1,
                             0, inorder.size() - 1);
}
} // namespace

SettingWin::SettingWin(QWidget *parent) : QWidget(parent) {
  ui = new Ui::setForm();
  ui->setupUi(this);

  connect(ui->btn_build, &QPushButton::clicked, this,
          &SettingWin::btnx_build_clicked);
}
SettingWin::~SettingWin() { delete ui; }
void SettingWin::btnx_build_clicked() {
  QString f1 = ui->LEfront->text();
  QString m1 = ui->LEmid->text();
  QStringList frontTxt = f1.split(',');
  QStringList midTxt = m1.split(',');
  qDebug() << frontTxt;
  qDebug() << midTxt;
  this->hide();
  emit buildTree(::buildTree(frontTxt, midTxt));
}
void SettingWin::closeEvent(QCloseEvent *event) { this->hide(); }