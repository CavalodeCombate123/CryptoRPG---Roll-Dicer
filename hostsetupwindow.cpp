#include "hostsetupwindow.h"
#include "ui_hostsetupwindow.h"

#include "mainwindow.h"

#include <QNetworkInterface>
#include <QHostAddress>

HostSetupWindow::HostSetupWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HostSetupWindow)
{
    ui->setupUi(this);

    // Atualiza o label assim que abrir
    refreshHostInfoLabel();

    // Se o usuário mudar a porta, atualiza o texto também
    connect(ui->portSpin, QOverload<int>::of(&QSpinBox::valueChanged),
            this, [this](int){ refreshHostInfoLabel(); });

    // OK
    connect(ui->btnPlay, &QDialogButtonBox::accepted, this, [this]() {

        QString nick = ui->nickEdit->text().trimmed();
        if (nick.isEmpty())
            nick = "Player";

        quint16 port = static_cast<quint16>(ui->portSpin->value());

        auto *room = new MainWindow();
        room->setAttribute(Qt::WA_DeleteOnClose);
        room->show();

        room->setNick(nick);
        room->startHost(port);

        // Reabre StartWindow quando fechar a sala
        if (parentWidget()) {
            QWidget *start = parentWidget();
            connect(room, &QObject::destroyed, start, [start]() {
                start->show();
            });
        }

        accept();
    });

    // Cancel
    connect(ui->btnPlay, &QDialogButtonBox::rejected, this, [this]() {
        reject();
    });
}

HostSetupWindow::~HostSetupWindow()
{
    delete ui;
}

QStringList HostSetupWindow::localIPv4List() const
{
    QStringList out;

    const auto ifaces = QNetworkInterface::allInterfaces();
    for (const QNetworkInterface& iface : ifaces) {
        // Ignora interfaces não-atvas
        if (!(iface.flags() & QNetworkInterface::IsUp) ||
            !(iface.flags() & QNetworkInterface::IsRunning))
            continue;

        // Ignora loopback aqui (127.0.0.1)
        if (iface.flags() & QNetworkInterface::IsLoopBack)
            continue;

        const auto entries = iface.addressEntries();
        for (const QNetworkAddressEntry& e : entries) {
            const QHostAddress ip = e.ip();
            if (ip.protocol() != QAbstractSocket::IPv4Protocol)
                continue;

            // Segurança extra: ignora 127.*
            if (ip.isLoopback())
                continue;

            out << ip.toString();
        }
    }

    out.removeDuplicates();

    // Se não achar nada (caso raro), pelo menos deixa explicado
    if (out.isEmpty()) {
        out << "(nenhum IPv4 detectado)";
    }

    return out;
}

void HostSetupWindow::refreshHostInfoLabel()
{
    const quint16 port = static_cast<quint16>(ui->portSpin->value());
    const QStringList ips = localIPv4List();

    QString text = "IPs para compartilhar com os jogadores:\n";
    for (const QString& ip : ips) {
        text += " - " + ip + ":" + QString::number(port) + "\n";
    }

    // Seu QLabel precisa se chamar lblHostInfo
    ui->lblHostInfo->setText(text);
}
