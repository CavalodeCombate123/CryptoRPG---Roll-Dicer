/********************************************************************************
** Form generated from reading UI file 'joinsetupwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOINSETUPWINDOW_H
#define UI_JOINSETUPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_JoinSetupWindow
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *panel;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *nickEdit;
    QLineEdit *hostIpEdit;
    QSpinBox *portSpin;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *JoinSetupWindow)
    {
        if (JoinSetupWindow->objectName().isEmpty())
            JoinSetupWindow->setObjectName("JoinSetupWindow");
        JoinSetupWindow->resize(400, 300);
        verticalLayout = new QVBoxLayout(JoinSetupWindow);
        verticalLayout->setObjectName("verticalLayout");
        panel = new QWidget(JoinSetupWindow);
        panel->setObjectName("panel");
        verticalLayout_2 = new QVBoxLayout(panel);
        verticalLayout_2->setObjectName("verticalLayout_2");
        nickEdit = new QLineEdit(panel);
        nickEdit->setObjectName("nickEdit");

        verticalLayout_2->addWidget(nickEdit);

        hostIpEdit = new QLineEdit(panel);
        hostIpEdit->setObjectName("hostIpEdit");

        verticalLayout_2->addWidget(hostIpEdit);

        portSpin = new QSpinBox(panel);
        portSpin->setObjectName("portSpin");

        verticalLayout_2->addWidget(portSpin);

        buttonBox = new QDialogButtonBox(panel);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout_2->addWidget(buttonBox);


        verticalLayout->addWidget(panel);


        retranslateUi(JoinSetupWindow);

        QMetaObject::connectSlotsByName(JoinSetupWindow);
    } // setupUi

    void retranslateUi(QDialog *JoinSetupWindow)
    {
        JoinSetupWindow->setWindowTitle(QCoreApplication::translate("JoinSetupWindow", "Dialog", nullptr));
        nickEdit->setPlaceholderText(QCoreApplication::translate("JoinSetupWindow", "Digite seu nome", nullptr));
        hostIpEdit->setPlaceholderText(QCoreApplication::translate("JoinSetupWindow", "Ex: 127.100.001", nullptr));
    } // retranslateUi

};

namespace Ui {
    class JoinSetupWindow: public Ui_JoinSetupWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOINSETUPWINDOW_H
