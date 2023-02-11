/********************************************************************************
** Form generated from reading UI file 'mainwin.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UUI_MAINWIN_H
#define UUI_MAINWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <kgraphicsview.h>

QT_BEGIN_NAMESPACE

class Ui_mainwin
{
public:
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *btn_build;
    QComboBox *cb_foreach;
    QPushButton *btn_foreach;
    QPushButton *btn_leave;
    QPushButton *btn_reverse;
    QPushButton *btn_clear;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_2;
    QWidget *tab;
    KGraphicsView *view;

    void setupUi(QWidget *mainwin)
    {
        if (mainwin->objectName().isEmpty())
            mainwin->setObjectName("mainwin");
        mainwin->resize(712, 477);
        horizontalLayout = new QHBoxLayout(mainwin);
        horizontalLayout->setObjectName("horizontalLayout");
        tabWidget = new QTabWidget(mainwin);
        tabWidget->setObjectName("tabWidget");
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        verticalLayout = new QVBoxLayout(tab_2);
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer = new QSpacerItem(20, 75, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        btn_build = new QPushButton(tab_2);
        btn_build->setObjectName("btn_build");

        verticalLayout->addWidget(btn_build);

        cb_foreach = new QComboBox(tab_2);
        cb_foreach->addItem(QString());
        cb_foreach->addItem(QString());
        cb_foreach->addItem(QString());
        cb_foreach->addItem(QString());
        cb_foreach->setObjectName("cb_foreach");

        verticalLayout->addWidget(cb_foreach);

        btn_foreach = new QPushButton(tab_2);
        btn_foreach->setObjectName("btn_foreach");

        verticalLayout->addWidget(btn_foreach);

        btn_leave = new QPushButton(tab_2);
        btn_leave->setObjectName("btn_leave");

        verticalLayout->addWidget(btn_leave);

        btn_reverse = new QPushButton(tab_2);
        btn_reverse->setObjectName("btn_reverse");

        verticalLayout->addWidget(btn_reverse);

        btn_clear = new QPushButton(tab_2);
        btn_clear->setObjectName("btn_clear");

        verticalLayout->addWidget(btn_clear);

        verticalSpacer_2 = new QSpacerItem(20, 74, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label_2 = new QLabel(tab_2);
        label_2->setObjectName("label_2");
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/m/img/green.jpg")));

        verticalLayout->addWidget(label_2);

        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        tabWidget->addTab(tab, QString());

        horizontalLayout->addWidget(tabWidget);

        view = new KGraphicsView(mainwin);
        view->setObjectName("view");

        horizontalLayout->addWidget(view);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 5);

        retranslateUi(mainwin);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(mainwin);
    } // setupUi

    void retranslateUi(QWidget *mainwin)
    {
        mainwin->setWindowTitle(QCoreApplication::translate("mainwin", "Widget", nullptr));
        btn_build->setText(QCoreApplication::translate("mainwin", "\347\224\237\346\210\220", nullptr));
        cb_foreach->setItemText(0, QCoreApplication::translate("mainwin", "\345\211\215\345\272\217", nullptr));
        cb_foreach->setItemText(1, QCoreApplication::translate("mainwin", "\344\270\255\345\272\217", nullptr));
        cb_foreach->setItemText(2, QCoreApplication::translate("mainwin", "\345\220\216\345\272\217", nullptr));
        cb_foreach->setItemText(3, QCoreApplication::translate("mainwin", "\345\261\202\347\272\247", nullptr));

        btn_foreach->setText(QCoreApplication::translate("mainwin", "\351\201\215\345\216\206", nullptr));
        btn_leave->setText(QCoreApplication::translate("mainwin", "\346\230\276\347\244\272\345\217\266\345\255\220\350\212\202\347\202\271", nullptr));
        btn_reverse->setText(QCoreApplication::translate("mainwin", "\345\217\215\350\275\254", nullptr));
        btn_clear->setText(QCoreApplication::translate("mainwin", "\346\270\205\347\251\272", nullptr));
        label_2->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("mainwin", "\351\273\230\350\256\244", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("mainwin", "\350\207\252\345\256\232\344\271\211", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainwin: public Ui_mainwin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UUI_MAINWIN_H
