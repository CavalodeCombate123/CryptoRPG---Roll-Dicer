/********************************************************************************
** Form generated from reading UI file 'startwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTWINDOW_H
#define UI_STARTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QPushButton *btnSolo;
    QPushButton *btnHost;
    QPushButton *btnJoin;
    QPushButton *btnBg;
    QPushButton *btnRestoreBg;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *StartWindow)
    {
        if (StartWindow->objectName().isEmpty())
            StartWindow->setObjectName("StartWindow");
        StartWindow->resize(800, 600);
        centralwidget = new QWidget(StartWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        btnSolo = new QPushButton(centralwidget);
        btnSolo->setObjectName("btnSolo");

        verticalLayout->addWidget(btnSolo);

        btnHost = new QPushButton(centralwidget);
        btnHost->setObjectName("btnHost");

        verticalLayout->addWidget(btnHost);

        btnJoin = new QPushButton(centralwidget);
        btnJoin->setObjectName("btnJoin");

        verticalLayout->addWidget(btnJoin);

        btnBg = new QPushButton(centralwidget);
        btnBg->setObjectName("btnBg");

        verticalLayout->addWidget(btnBg);

        btnRestoreBg = new QPushButton(centralwidget);
        btnRestoreBg->setObjectName("btnRestoreBg");

        verticalLayout->addWidget(btnRestoreBg);

        StartWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(StartWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        StartWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(StartWindow);
        statusbar->setObjectName("statusbar");
        StartWindow->setStatusBar(statusbar);

        retranslateUi(StartWindow);

        QMetaObject::connectSlotsByName(StartWindow);
    } // setupUi

    void retranslateUi(QMainWindow *StartWindow)
    {
        StartWindow->setWindowTitle(QCoreApplication::translate("StartWindow", "MainWindow", nullptr));
        btnSolo->setText(QCoreApplication::translate("StartWindow", "JOGAR (SOLO)", nullptr));
        btnHost->setText(QCoreApplication::translate("StartWindow", "HOST", nullptr));
        btnJoin->setText(QCoreApplication::translate("StartWindow", "ENTRAR", nullptr));
        btnBg->setText(QCoreApplication::translate("StartWindow", "BACKGROUND", nullptr));
        btnRestoreBg->setText(QCoreApplication::translate("StartWindow", "RESTAURAR", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartWindow: public Ui_StartWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTWINDOW_H
