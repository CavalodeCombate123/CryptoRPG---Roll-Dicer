/********************************************************************************
** Form generated from reading UI file 'hostsetupwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOSTSETUPWINDOW_H
#define UI_HOSTSETUPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HostSetupWindow
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *panel;
    QVBoxLayout *verticalLayout_2;
    QSpinBox *portSpin;
    QLabel *lblHostInfo;
    QLineEdit *nickEdit;
    QDialogButtonBox *btnPlay;

    void setupUi(QDialog *HostSetupWindow)
    {
        if (HostSetupWindow->objectName().isEmpty())
            HostSetupWindow->setObjectName("HostSetupWindow");
        HostSetupWindow->resize(400, 300);
        verticalLayout = new QVBoxLayout(HostSetupWindow);
        verticalLayout->setObjectName("verticalLayout");
        panel = new QWidget(HostSetupWindow);
        panel->setObjectName("panel");
        verticalLayout_2 = new QVBoxLayout(panel);
        verticalLayout_2->setObjectName("verticalLayout_2");
        portSpin = new QSpinBox(panel);
        portSpin->setObjectName("portSpin");

        verticalLayout_2->addWidget(portSpin);

        lblHostInfo = new QLabel(panel);
        lblHostInfo->setObjectName("lblHostInfo");
        lblHostInfo->setMinimumSize(QSize(0, 100));
        lblHostInfo->setWordWrap(true);

        verticalLayout_2->addWidget(lblHostInfo);

        nickEdit = new QLineEdit(panel);
        nickEdit->setObjectName("nickEdit");

        verticalLayout_2->addWidget(nickEdit);

        btnPlay = new QDialogButtonBox(panel);
        btnPlay->setObjectName("btnPlay");
        btnPlay->setOrientation(Qt::Orientation::Horizontal);
        btnPlay->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout_2->addWidget(btnPlay);


        verticalLayout->addWidget(panel);


        retranslateUi(HostSetupWindow);

        QMetaObject::connectSlotsByName(HostSetupWindow);
    } // setupUi

    void retranslateUi(QDialog *HostSetupWindow)
    {
        HostSetupWindow->setWindowTitle(QCoreApplication::translate("HostSetupWindow", "Dialog", nullptr));
        lblHostInfo->setText(QCoreApplication::translate("HostSetupWindow", "IP's para comparitlhar", nullptr));
        nickEdit->setText(QString());
        nickEdit->setPlaceholderText(QCoreApplication::translate("HostSetupWindow", "Digite seu nome", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HostSetupWindow: public Ui_HostSetupWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOSTSETUPWINDOW_H
