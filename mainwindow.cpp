#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPainter>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QFont>
#include <QSettings>
#include <QFileInfo>

// players_update a partir do set
static QJsonObject makePlayersUpdate(const QSet<QString>& playersSet) {
    QStringList list(playersSet.begin(), playersSet.end());
    list.sort(Qt::CaseInsensitive);

    QJsonObject msg;
    msg["type"] = "players_update";

    QJsonArray arr;
    for (const auto& p : list) arr.append(p);
    msg["players"] = arr;

    return msg;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Estilo
    QFile f(":/style/style.qss");
    if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        this->setStyleSheet(QString::fromUtf8(f.readAll()));
    }

    // Fontes (opcional)
    QFont font;
    font.setPointSize(14);
    ui->inputExpr->setFont(font);
    ui->outputBox->setFont(font);
    ui->historyList->setFont(font);
    ui->chatList->setFont(font);
    ui->playersList->setFont(font);

    QFont btnFont;
    btnFont.setPointSize(16);
    btnFont.setBold(true);
    ui->btnRoll->setFont(btnFont);

    // ======= CARREGA O BACKGROUND ESCOLHIDO NO MENU =======
    {
        QSettings s("CryptoRPG", "CryptoRPG");
        const QString saved = s.value("backgroundPath", "").toString();

        // Se existir e for arquivo mesmo, carrega. Se não, fica vazio e o paintEvent usa fallback.
        if (!saved.isEmpty() && QFileInfo::exists(saved)) {
            loadBackground(saved);
        } else {
            bgPixmap = QPixmap(); // vazio -> paintEvent vai usar cenario.jpg
            bgPath.clear();
            update();
        }
    }

    // Estado inicial
    ui->statusLabel->setText("Status: solo");

    // Rede
    server = new RoomServer(this);
    client = new RoomClient(this);

    connect(server, &RoomServer::log, this, [this](const QString& t){
        ui->statusLabel->setText("Status: " + t);
    });

    connect(client, &RoomClient::connected, this, [this](){
        if (server && server->isRunning()) {
            ui->statusLabel->setText("Status: host ativo (cliente local conectado)");
        } else {
            ui->statusLabel->setText("Status: conectado");
        }
    });

    connect(client, &RoomClient::disconnected, this, [this](){
        if (mode != GameMode::Solo) ui->statusLabel->setText("Status: offline");
    });

    connect(client, &RoomClient::error, this, [this](const QString& e){
        ui->statusLabel->setText("Status: erro - " + e);
    });

    // HOST: recebe mensagens
    connect(server, &RoomServer::messageReceived, this, [this](const QJsonObject& msg){
        const QString type = msg.value("type").toString();

        if (type == "join") {
            const QString user = msg.value("user").toString();
            players.insert(user);
            server->broadcast(makePlayersUpdate(players));
            return;
        }

        if (type == "roll_request") {
            const QString user = msg.value("user").toString();
            const QString expr = msg.value("expr").toString();

            RollResult r = engine.rollExpression(expr.toStdString());

            QJsonObject out;
            out["type"] = "roll_result";
            out["user"] = user;
            out["expr"] = expr;
            out["details"] = QString::fromStdString(r.detailsText);
            out["total"] = r.total;

            server->broadcast(out);
            return;
        }
    });

    // CLIENTE: recebe mensagens
    connect(client, &RoomClient::messageReceived, this, [this](const QJsonObject& msg){
        const QString type = msg.value("type").toString();

        if (type == "roll_result") {
            const QString user = msg.value("user").toString();
            const QString expr = msg.value("expr").toString();
            const QString details = msg.value("details").toString();
            const int total = msg.value("total").toInt();

            const QString line =
                user + " rolou " + expr + " => " + details + " | total: " + QString::number(total);

            ui->historyList->addItem(line);
            ui->outputBox->setPlainText(details + "\nTotal: " + QString::number(total));
            return;
        }

        if (type == "players_update") {
            ui->playersList->clear();
            QJsonArray arr = msg.value("players").toArray();
            for (const auto& v : arr) ui->playersList->addItem(v.toString());
            return;
        }

        if (type == "chat") {
            const QString user = msg.value("user").toString();
            const QString text = msg.value("text").toString();
            ui->chatList->addItem(user + ": " + text);
            ui->chatList->scrollToBottom();
            return;
        }
    });

    // Enviar chat
    auto sendChat = [this]() {
        QString text = ui->chatInput->text().trimmed();
        if (text.isEmpty()) return;

        const QString user = nickname.isEmpty() ? "Player" : nickname;

        if (client && client->isConnected()) {
            QJsonObject m;
            m["type"] = "chat";
            m["user"] = user;
            m["text"] = text;
            client->send(m);
        } else {
            ui->chatList->addItem(user + ": " + text);
            ui->chatList->scrollToBottom();
        }

        ui->chatInput->clear();
    };

    connect(ui->btnSendChat, &QPushButton::clicked, this, sendChat);
    connect(ui->chatInput, &QLineEdit::returnPressed, this, sendChat);

    // Roll
    connect(ui->btnRoll, &QPushButton::clicked, this, [this]() {
        const QString exprQ = ui->inputExpr->text().trimmed();

        if (exprQ.isEmpty()) {
            ui->outputBox->setPlainText("Digite uma expressao (ex: 3d8+2d10+5).");
            return;
        }

        if (client && client->isConnected()) {
            QJsonObject req;
            req["type"] = "roll_request";
            req["user"] = nickname.isEmpty() ? QString("Player") : nickname;
            req["expr"] = exprQ;
            client->send(req);
            return;
        }

        try {
            RollResult r = engine.rollExpression(exprQ.toStdString());
            QString out = QString::fromStdString(r.detailsText)
                          + "\nTotal: " + QString::number(r.total);
            ui->outputBox->setPlainText(out);
            ui->historyList->addItem(QString::fromStdString(r.historyLine));
        } catch (...) {
            ui->outputBox->setPlainText("Expressao invalida. Ex: 3d8+2d10+5 ou 2d20-3");
        }
    });

    // Sair
    connect(ui->btnLeave, &QPushButton::clicked, this, [this](){
        leaveRoom();
    });

    applySoloUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadBackground(const QString& path)
{
    QPixmap px(path);
    if (px.isNull()) return;

    bgPixmap = px;
    bgPath = path;

    // SALVA para todas as janelas futuras (StartWindow e MainWindow)
    QSettings s("CryptoRPG", "CryptoRPG");
    s.setValue("backgroundPath", bgPath);

    update();
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::SmoothPixmapTransform, true);

    QPixmap toDraw = bgPixmap;
    if (toDraw.isNull()) {
        toDraw.load(":/images/cenario.jpg"); // fallback padrão
    }

    if (!toDraw.isNull()) {
        QRect target = rect();

        QPixmap scaled = toDraw.scaled(
            target.size(),
            Qt::KeepAspectRatioByExpanding,
            Qt::SmoothTransformation
            );

        int x = (scaled.width()  - target.width())  / 2;
        int y = (scaled.height() - target.height()) / 2;
        QRect source(x, y, target.width(), target.height());

        p.drawPixmap(target, scaled, source);
    }

    QMainWindow::paintEvent(event);
}
void MainWindow::setNick(const QString& nick)
{
    nickname = nick.isEmpty() ? "Player" : nick;
}

void MainWindow::applySoloUi()
{
    mode = GameMode::Solo;

    // tabs: 0=Histórico, 1=Chat, 2=Jogadores
    ui->tabWidget->setTabVisible(1, false);
    ui->tabWidget->setTabVisible(2, false);
    ui->tabWidget->setCurrentIndex(0);

    ui->statusLabel->setText("Status: solo");
}

void MainWindow::applyOnlineUi()
{
    ui->tabWidget->setTabVisible(1, true);
    ui->tabWidget->setTabVisible(2, true);
}

void MainWindow::startSoloMode()
{
    if (client && client->isConnected()) client->disconnectFromHost();
    if (server && server->isRunning()) server->stop();

    players.clear();
    ui->playersList->clear();

    applySoloUi();
}

void MainWindow::startHost(quint16 port)
{
    mode = GameMode::OnlineHost;
    applyOnlineUi();

    players.clear();
    ui->playersList->clear();

    if (!server->start(port)) {
        ui->statusLabel->setText("Status: falha ao iniciar host");
        return;
    }

    // host entra como player
    players.insert(nickname);
    ui->playersList->addItem(nickname);

    ui->statusLabel->setText("Status: host ativo (porta " + QString::number(port) + ")");

    // host também vira cliente local
    client->connectTo("127.0.0.1", port);

    connect(client, &RoomClient::connected, this, [this](){
        QJsonObject join;
        join["type"] = "join";
        join["user"] = nickname;
        client->send(join);
    }, Qt::SingleShotConnection);
}

void MainWindow::startJoin(const QString& ip, quint16 port)
{
    mode = GameMode::OnlineClient;
    applyOnlineUi();

    players.clear();
    ui->playersList->clear();

    ui->statusLabel->setText("Status: conectando...");
    client->connectTo(ip, port);

    connect(client, &RoomClient::connected, this, [this](){
        QJsonObject join;
        join["type"] = "join";
        join["user"] = nickname;
        client->send(join);

        ui->statusLabel->setText("Status: conectado");
    }, Qt::SingleShotConnection);
}

void MainWindow::leaveRoom()
{
    if (client && client->isConnected()) client->disconnectFromHost();
    if (server && server->isRunning()) server->stop();

    close();
}
