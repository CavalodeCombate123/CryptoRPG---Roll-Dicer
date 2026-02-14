#include "joinsetupwindow.h"
#include "ui_joinsetupwindow.h"

#include "mainwindow.h"

JoinSetupWindow::JoinSetupWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::JoinSetupWindow)
{
    ui->setupUi(this);

    ui->portSpin->setMinimum(1);
    if (ui->portSpin->value() == 0) ui->portSpin->setValue(7777);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, [this]() {
        QString nick = ui->nickEdit->text().trimmed();
        if (nick.isEmpty()) nick = "Player";

        QString ip = ui->hostIpEdit->text().trimmed();
        if (ip.isEmpty()) ip = "127.0.0.1";

        quint16 port = static_cast<quint16>(ui->portSpin->value());

        auto *room = new MainWindow();
        room->setAttribute(Qt::WA_DeleteOnClose);
        room->show();

        room->setNick(nick);
        room->startJoin(ip, port);

        if (parentWidget()) {
            QWidget *start = parentWidget();
            connect(room, &QObject::destroyed, start, [start]() { start->show(); });
        }

        accept();
    });

    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, [this]() {
        reject();
    });
}

JoinSetupWindow::~JoinSetupWindow()
{
    delete ui;
}
