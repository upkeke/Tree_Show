/********************************************************************************
** Form generated from reading UI file 'BinaryTreeWin.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UIX_BINARYTREEWIN_H
#define UIX_BINARYTREEWIN_H

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
    QAction *actrefresh;
    QAction *actionadd;
    QAction *actionleaf;
    QAction *actiondepth;
    QAction *actionset;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGraphicsView *view;
    QMenuBar *menubar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *BinaryTreeWin)
    {
        if (BinaryTreeWin->objectName().isEmpty())
            BinaryTreeWin->setObjectName("BinaryTreeWin");
        BinaryTreeWin->resize(529, 600);
        actionbuild = new QAction(BinaryTreeWin);
        actionbuild->setObjectName("actionbuild");
        actionbuild->setCheckable(false);
        actionbuild->setChecked(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/mainwin/img/build.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/k/img/clearNode.png"), QSize(), QIcon::Normal, QIcon::On);
        actionbuild->setIcon(icon);
        actrefresh = new QAction(BinaryTreeWin);
        actrefresh->setObjectName("actrefresh");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/mainwin/img/refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        actrefresh->setIcon(icon1);
        actionadd = new QAction(BinaryTreeWin);
        actionadd->setObjectName("actionadd");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/mainwin/img/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionadd->setIcon(icon2);
        actionleaf = new QAction(BinaryTreeWin);
        actionleaf->setObjectName("actionleaf");
        actionleaf->setCheckable(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/mainwin/img/leaves.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionleaf->setIcon(icon3);
        actiondepth = new QAction(BinaryTreeWin);
        actiondepth->setObjectName("actiondepth");
        actiondepth->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/mainwin/img/height.png"), QSize(), QIcon::Normal, QIcon::Off);
        actiondepth->setIcon(icon4);
        actionset = new QAction(BinaryTreeWin);
        actionset->setObjectName("actionset");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/mainwin/img/setting.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionset->setIcon(icon5);
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
        menubar->setGeometry(QRect(0, 0, 529, 22));
        BinaryTreeWin->setMenuBar(menubar);
        toolBar = new QToolBar(BinaryTreeWin);
        toolBar->setObjectName("toolBar");
        BinaryTreeWin->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionbuild);
        toolBar->addAction(actrefresh);
        toolBar->addAction(actionadd);
        toolBar->addAction(actionleaf);
        toolBar->addAction(actiondepth);
        toolBar->addAction(actionset);

        retranslateUi(BinaryTreeWin);

        QMetaObject::connectSlotsByName(BinaryTreeWin);
    } // setupUi

    void retranslateUi(QMainWindow *BinaryTreeWin)
    {
        BinaryTreeWin->setWindowTitle(QCoreApplication::translate("BinaryTreeWin", "\344\272\214\345\217\211\346\240\221\345\217\257\350\247\206\345\214\226", nullptr));
        actionbuild->setText(QCoreApplication::translate("BinaryTreeWin", "build", nullptr));
#if QT_CONFIG(tooltip)
        actionbuild->setToolTip(QCoreApplication::translate("BinaryTreeWin", "\347\224\237\346\210\220\344\272\214\345\217\211\346\240\221", nullptr));
#endif // QT_CONFIG(tooltip)
        actrefresh->setText(QCoreApplication::translate("BinaryTreeWin", "\345\210\267\346\226\260", nullptr));
#if QT_CONFIG(tooltip)
        actrefresh->setToolTip(QCoreApplication::translate("BinaryTreeWin", "\345\244\215\345\216\237\346\257\217\344\270\252\350\212\202\347\202\271\347\232\204\351\242\234\350\211\262", nullptr));
#endif // QT_CONFIG(tooltip)
        actionadd->setText(QCoreApplication::translate("BinaryTreeWin", "\346\267\273\345\212\240\350\212\202\347\202\271", nullptr));
#if QT_CONFIG(tooltip)
        actionadd->setToolTip(QCoreApplication::translate("BinaryTreeWin", "\346\267\273\345\212\240\350\212\202\347\202\271", nullptr));
#endif // QT_CONFIG(tooltip)
        actionleaf->setText(QCoreApplication::translate("BinaryTreeWin", "\346\230\276\347\244\272\345\217\266\345\255\220\350\212\202\347\202\271", nullptr));
#if QT_CONFIG(tooltip)
        actionleaf->setToolTip(QCoreApplication::translate("BinaryTreeWin", "\346\230\276\347\244\272\345\217\266\345\255\220\350\212\202\347\202\271", nullptr));
#endif // QT_CONFIG(tooltip)
        actiondepth->setText(QCoreApplication::translate("BinaryTreeWin", "\346\230\276\347\244\272\346\267\261\345\272\246", nullptr));
#if QT_CONFIG(tooltip)
        actiondepth->setToolTip(QCoreApplication::translate("BinaryTreeWin", "\346\230\276\347\244\272\346\267\261\345\272\246", nullptr));
#endif // QT_CONFIG(tooltip)
        actionset->setText(QCoreApplication::translate("BinaryTreeWin", "set", nullptr));
#if QT_CONFIG(tooltip)
        actionset->setToolTip(QCoreApplication::translate("BinaryTreeWin", "\350\256\276\347\275\256", nullptr));
#endif // QT_CONFIG(tooltip)
        toolBar->setWindowTitle(QCoreApplication::translate("BinaryTreeWin", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BinaryTreeWin: public Ui_BinaryTreeWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UIX_BINARYTREEWIN_H
