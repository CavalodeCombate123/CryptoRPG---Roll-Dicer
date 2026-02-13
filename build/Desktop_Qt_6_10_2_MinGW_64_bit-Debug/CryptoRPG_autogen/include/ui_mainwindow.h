/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *inputExpr;
    QPushButton *btnRoll;
    QPlainTextEdit *outputBox;
    QListWidget *historyList;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        inputExpr = new QLineEdit(centralwidget);
        inputExpr->setObjectName("inputExpr");

        verticalLayout->addWidget(inputExpr);

        btnRoll = new QPushButton(centralwidget);
        btnRoll->setObjectName("btnRoll");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnRoll->sizePolicy().hasHeightForWidth());
        btnRoll->setSizePolicy(sizePolicy);
        btnRoll->setMinimumSize(QSize(0, 60));

        verticalLayout->addWidget(btnRoll);

        outputBox = new QPlainTextEdit(centralwidget);
        outputBox->setObjectName("outputBox");
        outputBox->setMinimumSize(QSize(0, 200));
        outputBox->setReadOnly(true);

        verticalLayout->addWidget(outputBox);

        historyList = new QListWidget(centralwidget);
        historyList->setObjectName("historyList");
        historyList->setMinimumSize(QSize(0, 160));

        verticalLayout->addWidget(historyList);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        inputExpr->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: 3d8+2d10+5", nullptr));
        btnRoll->setText(QCoreApplication::translate("MainWindow", "ROLL", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
