
#pragma once
#ifndef __BUILDTREE__
#define __BUILDTREE__

#include <QStrNode.hpp>
#include <QStringList>
#include <iostream>
#include <unordered_map>
#include <vector>


using namespace std;
// 通过前序和中序遍历建立一颗二叉树
/*
在前序遍历中找到第一个节点，这个节点就是当前的根节点。
在中序遍历中找到根节点所在的位置，该位置左侧的所有节点都是根节点的左子树，右侧的所有节点都是根节点的右子树。
根据左子树和右子树的节点数，可以在前序遍历中划分出左子树和右子树的节点集合。
递归地重建左子树和右子树，然后将它们作为根节点的左右子树连接到根节点上。
*/
// Definition for a binary tree node.
// struct TreeNode {
//     int val;
//     TreeNode *left;
//     TreeNode *right;
//     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
// };
using namespace sbt;
class Solution {
public:
  NodePtr buildTree(QStringList &preorder, QStringList &inorder) {
    unordered_map<QString, int> index; // 哈希表记录中序遍历中每个节点值的下标
    for (int i = 0; i < inorder.size(); i++) {
      index[inorder[i]] = i;
    }
    return buildTreeByFrontMid(preorder, inorder, index, 0, preorder.size() - 1, 0,
                           inorder.size() - 1);
  }

private:
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
};

#endif