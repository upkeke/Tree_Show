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
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainwin
{
public:
    QHBoxLayout *horizontalLayout;
    QGraphicsView *view;
    QVBoxLayout *verticalLayout;
    QPushButton *btn_build;
    QSpacerItem *verticalSpacer;
    QComboBox *cb_foreach;
    QPushButton *btn_foreach;
    QSpacerItem *verticalSpacer_2;
    QPushButton *btn_reverse;

    void setupUi(QWidget *mainwin)
    {
        if (mainwin->objectName().isEmpty())
            mainwin->setObjectName("mainwin");
        mainwin->resize(412, 343);
        horizontalLayout = new QHBoxLayout(mainwin);
        horizontalLayout->setObjectName("horizontalLayout");
        view = new QGraphicsView(mainwin);
        view->setObjectName("view");

        horizontalLayout->addWidget(view);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        btn_build = new QPushButton(mainwin);
        btn_build->setObjectName("btn_build");

        verticalLayout->addWidget(btn_build);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        cb_foreach = new QComboBox(mainwin);
        cb_foreach->addItem(QString());
        cb_foreach->addItem(QString());
        cb_foreach->addItem(QString());
        cb_foreach->setObjectName("cb_foreach");

        verticalLayout->addWidget(cb_foreach);

        btn_foreach = new QPushButton(mainwin);
        btn_foreach->setObjectName("btn_foreach");

        verticalLayout->addWidget(btn_foreach);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        btn_reverse = new QPushButton(mainwin);
        btn_reverse->setObjectName("btn_reverse");

        verticalLayout->addWidget(btn_reverse);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(mainwin);

        QMetaObject::connectSlotsByName(mainwin);
    } // setupUi

    void retranslateUi(QWidget *mainwin)
    {
        mainwin->setWindowTitle(QCoreApplication::translate("mainwin", "Widget", nullptr));
        btn_build->setText(QCoreApplication::translate("mainwin", "\347\224\237\346\210\220", nullptr));
        cb_foreach->setItemText(0, QCoreApplication::translate("mainwin", "\345\211\215\345\272\217", nullptr));
        cb_foreach->setItemText(1, QCoreApplication::translate("mainwin", "\344\270\255\345\272\217", nullptr));
        cb_foreach->setItemText(2, QCoreApplication::translate("mainwin", "\345\220\216\345\272\217", nullptr));

        btn_foreach->setText(QCoreApplication::translate("mainwin", "\351\201\215\345\216\206", nullptr));
        btn_reverse->setText(QCoreApplication::translate("mainwin", "\345\217\215\350\275\254", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainwin: public Ui_mainwin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UUI_MAINWIN_H
