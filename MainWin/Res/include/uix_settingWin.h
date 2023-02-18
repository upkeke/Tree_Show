/********************************************************************************
** Form generated from reading UI file 'settingWin.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UIX_SETTINGWIN_H
#define UIX_SETTINGWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_setForm
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *LEfront;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *LEmid;
    QPushButton *btn_build;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *setForm)
    {
        if (setForm->objectName().isEmpty())
            setForm->setObjectName("setForm");
        setForm->resize(426, 300);
        verticalLayout = new QVBoxLayout(setForm);
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(setForm);
        groupBox->setObjectName("groupBox");
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        LEfront = new QLineEdit(groupBox);
        LEfront->setObjectName("LEfront");

        horizontalLayout->addWidget(LEfront);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        LEmid = new QLineEdit(groupBox);
        LEmid->setObjectName("LEmid");

        horizontalLayout_2->addWidget(LEmid);


        verticalLayout_2->addLayout(horizontalLayout_2);

        btn_build = new QPushButton(groupBox);
        btn_build->setObjectName("btn_build");

        verticalLayout_2->addWidget(btn_build);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        verticalLayout->addWidget(groupBox);


        retranslateUi(setForm);

        QMetaObject::connectSlotsByName(setForm);
    } // setupUi

    void retranslateUi(QWidget *setForm)
    {
        setForm->setWindowTitle(QCoreApplication::translate("setForm", "\350\256\276\347\275\256", nullptr));
        groupBox->setTitle(QCoreApplication::translate("setForm", "\350\212\202\347\202\271\346\225\260\346\215\256", nullptr));
        label->setText(QCoreApplication::translate("setForm", "\345\211\215\345\272\217\351\201\215\345\216\206", nullptr));
        label_2->setText(QCoreApplication::translate("setForm", "\344\270\255\345\272\217\351\201\215\345\216\206", nullptr));
        btn_build->setText(QCoreApplication::translate("setForm", "build", nullptr));
    } // retranslateUi

};

namespace Ui {
    class setForm: public Ui_setForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UIX_SETTINGWIN_H
