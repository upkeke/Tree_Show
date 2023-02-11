/********************************************************************************
** Form generated from reading UI file 'BinaryTreeWin.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef BINARYTREEWIN_H
#define BINARYTREEWIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BinaryTreeWin
{
public:
    QAction *actionbuild;
    QAction *actAddNode;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGraphicsView *view;
    QMenuBar *menubar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *BinaryTreeWin)
    {
        if (BinaryTreeWin->objectName().isEmpty())
            BinaryTreeWin->setObjectName("BinaryTreeWin");
        BinaryTreeWin->resize(643, 600);
        actionbuild = new QAction(BinaryTreeWin);
        actionbuild->setObjectName("actionbuild");
        actAddNode = new QAction(BinaryTreeWin);
        actAddNode->setObjectName("actAddNode");
        centralwidget = new QWidget(BinaryTreeWin);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        view = new QGraphicsView(centralwidget);
        view->setObjectName("view");

        verticalLayout->addWidget(view);

        BinaryTreeWin->setCentralWidget(centralwidget);
        menubar = new QMenuBar(BinaryTreeWin);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 643, 22));
        BinaryTreeWin->setMenuBar(menubar);
        toolBar = new QToolBar(BinaryTreeWin);
        toolBar->setObjectName("toolBar");
        BinaryTreeWin->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionbuild);

        retranslateUi(BinaryTreeWin);

        QMetaObject::connectSlotsByName(BinaryTreeWin);
    } // setupUi

    void retranslateUi(QMainWindow *BinaryTreeWin)
    {
        BinaryTreeWin->setWindowTitle(QCoreApplication::translate("BinaryTreeWin", "\344\272\214\345\217\211\346\240\221\345\217\257\350\247\206\345\214\226", nullptr));
        actionbuild->setText(QCoreApplication::translate("BinaryTreeWin", "build", nullptr));
        actAddNode->setText(QCoreApplication::translate("BinaryTreeWin", "\346\267\273\345\212\240", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("BinaryTreeWin", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BinaryTreeWin: public Ui_BinaryTreeWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // BINARYTREEWIN_H
