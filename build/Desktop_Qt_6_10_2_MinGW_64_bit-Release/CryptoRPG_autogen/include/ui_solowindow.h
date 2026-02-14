/********************************************************************************
** Form generated from reading UI file 'solowindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOLOWINDOW_H
#define UI_SOLOWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SoloWindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SoloWindow)
    {
        if (SoloWindow->objectName().isEmpty())
            SoloWindow->setObjectName("SoloWindow");
        SoloWindow->resize(800, 600);
        centralwidget = new QWidget(SoloWindow);
        centralwidget->setObjectName("centralwidget");
        SoloWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SoloWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        SoloWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SoloWindow);
        statusbar->setObjectName("statusbar");
        SoloWindow->setStatusBar(statusbar);

        retranslateUi(SoloWindow);

        QMetaObject::connectSlotsByName(SoloWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SoloWindow)
    {
        SoloWindow->setWindowTitle(QCoreApplication::translate("SoloWindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SoloWindow: public Ui_SoloWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOLOWINDOW_H
