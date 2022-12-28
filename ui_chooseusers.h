/********************************************************************************
** Form generated from reading UI file 'chooseusers.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEUSERS_H
#define UI_CHOOSEUSERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChooseUsers
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit;
    QListWidget *listWidget;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *ChooseUsers)
    {
        if (ChooseUsers->objectName().isEmpty())
            ChooseUsers->setObjectName("ChooseUsers");
        ChooseUsers->resize(200, 390);
        verticalLayoutWidget = new QWidget(ChooseUsers);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(20, 20, 158, 351));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName("label_3");

        horizontalLayout->addWidget(label_3);


        verticalLayout->addLayout(horizontalLayout);

        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName("label_4");

        verticalLayout->addWidget(label_4);

        lineEdit = new QLineEdit(verticalLayoutWidget);
        lineEdit->setObjectName("lineEdit");

        verticalLayout->addWidget(lineEdit);

        listWidget = new QListWidget(verticalLayoutWidget);
        listWidget->setObjectName("listWidget");

        verticalLayout->addWidget(listWidget);

        buttonBox = new QDialogButtonBox(verticalLayoutWidget);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ChooseUsers);

        QMetaObject::connectSlotsByName(ChooseUsers);
    } // setupUi

    void retranslateUi(QWidget *ChooseUsers)
    {
        ChooseUsers->setWindowTitle(QCoreApplication::translate("ChooseUsers", "Form", nullptr));
        label->setText(QCoreApplication::translate("ChooseUsers", "<html><head/><body><p><span style=\" font-weight:700;\">Who do you wanna add?</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("ChooseUsers", "Count:", nullptr));
        label_3->setText(QCoreApplication::translate("ChooseUsers", "0", nullptr));
        label_4->setText(QCoreApplication::translate("ChooseUsers", "Users:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChooseUsers: public Ui_ChooseUsers {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEUSERS_H
