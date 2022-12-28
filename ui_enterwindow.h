/********************************************************************************
** Form generated from reading UI file 'enterwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENTERWINDOW_H
#define UI_ENTERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EnterWindow
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QLabel *label_3;
    QPushButton *pushButton_2;
    QLabel *label_6;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_5;
    QLabel *label_4;

    void setupUi(QDialog *EnterWindow)
    {
        if (EnterWindow->objectName().isEmpty())
            EnterWindow->setObjectName("EnterWindow");
        EnterWindow->resize(315, 330);
        verticalLayoutWidget = new QWidget(EnterWindow);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(80, 80, 160, 184));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        lineEdit_2 = new QLineEdit(verticalLayoutWidget);
        lineEdit_2->setObjectName("lineEdit_2");

        verticalLayout->addWidget(lineEdit_2);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        lineEdit = new QLineEdit(verticalLayoutWidget);
        lineEdit->setObjectName("lineEdit");

        verticalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName("pushButton");

        verticalLayout->addWidget(pushButton);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName("pushButton_2");

        verticalLayout->addWidget(pushButton_2);

        label_6 = new QLabel(EnterWindow);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(100, 10, 121, 61));
        verticalLayoutWidget_2 = new QWidget(EnterWindow);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(10, 280, 261, 41));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(verticalLayoutWidget_2);
        label_5->setObjectName("label_5");

        verticalLayout_2->addWidget(label_5);

        label_4 = new QLabel(verticalLayoutWidget_2);
        label_4->setObjectName("label_4");

        verticalLayout_2->addWidget(label_4);


        retranslateUi(EnterWindow);

        QMetaObject::connectSlotsByName(EnterWindow);
    } // setupUi

    void retranslateUi(QDialog *EnterWindow)
    {
        EnterWindow->setWindowTitle(QCoreApplication::translate("EnterWindow", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("EnterWindow", "Nickname/Login", nullptr));
        label_2->setText(QCoreApplication::translate("EnterWindow", "Password", nullptr));
        pushButton->setText(QCoreApplication::translate("EnterWindow", "Enter", nullptr));
        label_3->setText(QCoreApplication::translate("EnterWindow", "                        or", nullptr));
        pushButton_2->setText(QCoreApplication::translate("EnterWindow", "Registration", nullptr));
        label_6->setText(QCoreApplication::translate("EnterWindow", "<html><head/><body><h1 style=\" margin-top:18px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:xx-large; font-weight:700; font-style:italic;\">Welcome!</span></h1></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("EnterWindow", "TextAboutLogin", nullptr));
        label_4->setText(QCoreApplication::translate("EnterWindow", "TextAboutPassword", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EnterWindow: public Ui_EnterWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENTERWINDOW_H
