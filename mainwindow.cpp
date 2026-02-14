#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>
#include <QFileDialog>
#include <QStandardPaths>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QFont>

// Cria mensagem players_update a partir do set
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
    QSettings s("CryptoRPG", "CryptoRPG");
    QString saved = s.value("backgroundPath", "").toString();
    if (!saved.isEmpty()) {
        loadBackground(saved);
    }

    connect(ui->btnBg, &QPushButton::clicked, this, [this](){
        QString file = QFileDialog::getOpenFileName(
            this,
            "Escolher background",
            QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
            "Imagens (*.png *.jpg *.jpeg)"
            );

        if (!file.isEmpty()) {
            loadBackground(file);
        }
    });


    // Carrega estilo
    QFile f(":/style/style.qss");
    if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        this->setStyleSheet(QString::fromUtf8(f.readAll()));
    }

    // Fontes
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

    // Estado inicial
    ui->statusLabel->setText("Status: offline");
    ui->btnStopHost->setEnabled(false);

    // Rede
    server = new RoomServer(this);
    client = new RoomClient(this);

    connect(server, &RoomServer::log, this, [this](const QString& t){
        ui->statusLabel->setText("Status: " + t);
    });

    connect(client, &RoomClient::connected, this, [this](){
        ui->statusLabel->setText("Status: conectado");
        ui->btnJoin->setEnabled(true);
    });

    connect(client, &RoomClient::disconnected, this, [this](){
        ui->statusLabel->setText("Status: offline");

        // Se não estiver host, reativa botões
        if (!(server && server->isRunning())) {
            ui->btnJoin->setEnabled(true);
            ui->btnHost->setEnabled(true);
            ui->btnStopHost->setEnabled(false);
        }
    });

    connect(client, &RoomClient::error, this, [this](const QString& e){
        ui->statusLabel->setText("Status: erro - " + e);

        if (!(server && server->isRunning())) {
            ui->btnJoin->setEnabled(true);
        }
    });

    // HOST: recebe mensagens dos clientes e decide o que fazer
    connect(server, &RoomServer::messageReceived, this, [this](const QJsonObject& msg){
        const QString type = msg.value("type").toString();

        if (type == "join") {
            const QString user = msg.value("user").toString();
            ui->historyList->addItem("[JOIN] " + user);

            players.insert(user);
            server->broadcast(makePlayersUpdate(players)); // mantém isso

            // NÃO retransmite o join aqui (o RoomServer já retransmite sozinho)
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

            server->broadcast(out); // aqui continua, porque isso é novo (o server não gera sozinho)
            return;
        }

        if (type == "chat") {
            // NÃO retransmite o chat aqui (o RoomServer já retransmite sozinho)
            return;
        }
    });


    // CLIENTE: recebe mensagens e atualiza UI
    connect(client, &RoomClient::messageReceived, this, [this](const QJsonObject& msg){
        const QString type = msg.value("type").toString();

        if (type == "roll_result") {
            const QString user = msg.value("user").toString();
            const QString expr = msg.value("expr").toString();
            const QString details = msg.value("details").toString();
            const int total = msg.value("total").toInt();

            const QString line =
                user + " rolou " + expr + " => " + details + " | total:" + QString::number(total);

            ui->historyList->addItem(line);
            ui->outputBox->setPlainText(details + "\nTotal: " + QString::number(total));
            return;
        }

        if (type == "join") {
            const QString user = msg.value("user").toString();
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

    // Enviar chat (botão + Enter)
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
            // offline: mostra local
            ui->chatList->addItem(user + ": " + text);
            ui->chatList->scrollToBottom();
        }

        ui->chatInput->clear();
    };

    connect(ui->btnSendChat, &QPushButton::clicked, this, sendChat);
    connect(ui->chatInput, &QLineEdit::returnPressed, this, sendChat);

    // BOTÃO HOST
    connect(ui->btnHost, &QPushButton::clicked, this, [this](){
        nickname = ui->nickEdit->text().trimmed();
        if (nickname.isEmpty()) nickname = "Player";

        const quint16 port = static_cast<quint16>(ui->portSpin->value());

        if (!server->start(port)) {
            ui->statusLabel->setText("Status: falha ao iniciar host");
            return;
        }

        // UI
        ui->btnHost->setEnabled(false);
        ui->btnJoin->setEnabled(false);
        ui->btnStopHost->setEnabled(true);

        // Lista de jogadores no host começa com ele mesmo
        players.clear();
        players.insert(nickname);
        ui->playersList->clear();
        ui->playersList->addItem(nickname);

        // Host também vira cliente local
        client->connectTo("127.0.0.1", port);

        // Envia join quando conectar
        connect(client, &RoomClient::connected, this, [this](){
            QJsonObject join;
            join["type"] = "join";
            join["user"] = nickname;
            client->send(join);
        }, Qt::SingleShotConnection);

        ui->statusLabel->setText("Status: host ativo (porta " + QString::number(port) + ")");
    });

    // BOTÃO ENTRAR
    connect(ui->btnJoin, &QPushButton::clicked, this, [this](){
        nickname = ui->nickEdit->text().trimmed();
        if (nickname.isEmpty()) nickname = "Player";

        QString hostIp = ui->hostIpEdit->text().trimmed();
        if (hostIp.isEmpty()) hostIp = "127.0.0.1";

        const quint16 port = static_cast<quint16>(ui->portSpin->value());

        ui->btnJoin->setEnabled(false);
        ui->statusLabel->setText("Status: conectando...");

        client->connectTo(hostIp, port);

        connect(client, &RoomClient::connected, this, [this](){
            QJsonObject join;
            join["type"] = "join";
            join["user"] = nickname;
            client->send(join);
        }, Qt::SingleShotConnection);
    });

    // BOTÃO ENCERRAR SALA (host)
    connect(ui->btnStopHost, &QPushButton::clicked, this, [this]() {
        if (client && client->isConnected()) {
            client->disconnect();
        }
        if (server && server->isRunning()) {
            server->stop();
        }

        players.clear();
        ui->playersList->clear();

        ui->statusLabel->setText("Status: offline");
        ui->btnHost->setEnabled(true);
        ui->btnJoin->setEnabled(true);
        ui->btnStopHost->setEnabled(false);
    });

    // BOTÃO ROLL (rede se conectado, local se offline)
    connect(ui->btnRoll, &QPushButton::clicked, this, [this]() {
        const QString exprQ = ui->inputExpr->text().trimmed();

        if (exprQ.isEmpty()) {
            ui->outputBox->setPlainText("Digite uma expressao (ex: 3d8+2d10+5).");
            return;
        }

        // Rede: manda pro host calcular
        if (client && client->isConnected()) {
            QJsonObject req;
            req["type"] = "roll_request";
            req["user"] = nickname.isEmpty() ? QString("Player") : nickname;
            req["expr"] = exprQ;
            client->send(req);
            return;
        }

        // Offline: rolagem local
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
}
void MainWindow::loadBackground(const QString& path)
{
    QPixmap px(path);
    if (px.isNull()) return;

    bgPixmap = px;
    bgPath = path;

    // salva nas configurações pra lembrar depois
    QSettings s("CryptoRPG", "CryptoRPG");
    s.setValue("backgroundPath", bgPath);

    update(); // redesenha a janela
}
void MainWindow::paintEvent(QPaintEvent* event)
{
    // desenha o fundo primeiro
    if (!bgPixmap.isNull()) {
        QPainter p(this);
        p.setRenderHint(QPainter::SmoothPixmapTransform, true);

        // ocupa a área inteira da janela
        QRect target = rect();

        // escala pra preencher (sem distorcer) e corta o excesso (central)
        QPixmap scaled = bgPixmap.scaled(
            target.size(),
            Qt::KeepAspectRatioByExpanding,
            Qt::SmoothTransformation
            );

        // centraliza o crop
        int x = (scaled.width()  - target.width())  / 2;
        int y = (scaled.height() - target.height()) / 2;
        QRect source(x, y, target.width(), target.height());

        p.drawPixmap(target, scaled, source);
    }

    // deixa o Qt desenhar o resto (widgets, bordas, etc.)
    QMainWindow::paintEvent(event);
}


MainWindow::~MainWindow()
{
    delete ui;
}
