#include "solowindow.h"
#include "ui_solowindow.h"

#include "mainwindow.h"

SoloWindow::SoloWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SoloWindow)
{
    ui->setupUi(this);

    auto *room = new MainWindow();
    room->setAttribute(Qt::WA_DeleteOnClose);
    room->show();
    room->startSoloMode();


    this->close();
}

SoloWindow::~SoloWindow()
{
    delete ui;
}
