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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QPushButton *btnLeave;
    QLabel *statusLabel;
    QLineEdit *inputExpr;
    QPushButton *btnRoll;
    QPlainTextEdit *outputBox;
    QTabWidget *tabWidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QListWidget *historyList;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_4;
    QListWidget *chatList;
    QPushButton *btnSendChat;
    QLineEdit *chatInput;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_2;
    QListWidget *playersList;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1252, 732);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        btnLeave = new QPushButton(centralwidget);
        btnLeave->setObjectName("btnLeave");

        verticalLayout->addWidget(btnLeave);

        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName("statusLabel");

        verticalLayout->addWidget(statusLabel);

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
        btnRoll->setMinimumSize(QSize(0, 50));

        verticalLayout->addWidget(btnRoll);

        outputBox = new QPlainTextEdit(centralwidget);
        outputBox->setObjectName("outputBox");
        outputBox->setMinimumSize(QSize(0, 100));
        outputBox->setReadOnly(true);

        verticalLayout->addWidget(outputBox);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setMinimumSize(QSize(0, 50));
        tabWidget->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
        widget = new QWidget();
        widget->setObjectName("widget");
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        historyList = new QListWidget(widget);
        historyList->setObjectName("historyList");

        verticalLayout_3->addWidget(historyList);

        tabWidget->addTab(widget, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        verticalLayout_4 = new QVBoxLayout(tab_2);
        verticalLayout_4->setObjectName("verticalLayout_4");
        chatList = new QListWidget(tab_2);
        chatList->setObjectName("chatList");

        verticalLayout_4->addWidget(chatList);

        btnSendChat = new QPushButton(tab_2);
        btnSendChat->setObjectName("btnSendChat");

        verticalLayout_4->addWidget(btnSendChat);

        chatInput = new QLineEdit(tab_2);
        chatInput->setObjectName("chatInput");

        verticalLayout_4->addWidget(chatInput);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        verticalLayout_2 = new QVBoxLayout(tab_3);
        verticalLayout_2->setObjectName("verticalLayout_2");
        playersList = new QListWidget(tab_3);
        playersList->setObjectName("playersList");

        verticalLayout_2->addWidget(playersList);

        tabWidget->addTab(tab_3, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1252, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnLeave->setText(QCoreApplication::translate("MainWindow", "SAIR", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "Status: Offline", nullptr));
        inputExpr->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: 3d8+2d10+5", nullptr));
        btnRoll->setText(QCoreApplication::translate("MainWindow", "ROLL", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(widget), QCoreApplication::translate("MainWindow", "Hist\303\263rico", nullptr));
        btnSendChat->setText(QCoreApplication::translate("MainWindow", "ENVIAR", nullptr));
        chatInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "Digite uma mensagem...", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Chat", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Jogadores", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
