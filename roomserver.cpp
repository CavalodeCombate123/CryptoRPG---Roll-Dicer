#include "roomserver.h"
#include "roomprotocol.h"
#include <QJsonDocument>

RoomServer::RoomServer(QObject* parent) : QObject(parent) {
    connect(&m_server, &QTcpServer::newConnection, this, &RoomServer::onNewConnection);
}

bool RoomServer::start(quint16 port) {
    if (m_server.isListening()) m_server.close();
    bool ok = m_server.listen(QHostAddress::AnyIPv4, port);
    emit log(ok ? QString("Host iniciado na porta %1").arg(port)
                : QString("Falha ao iniciar host: %1").arg(m_server.errorString()));
    return ok;
}

void RoomServer::stop() {
    for (auto* s : m_clients) {
        s->disconnectFromHost();
        s->deleteLater();
    }
    m_clients.clear();
    m_server.close();
    emit log("Host encerrado.");
}

bool RoomServer::isRunning() const { return m_server.isListening(); }

void RoomServer::broadcast(const QJsonObject& msg) {
    QByteArray data = packJsonLine(msg);
    for (auto* s : m_clients) {
        if (s && s->state() == QAbstractSocket::ConnectedState) s->write(data);
    }
}

void RoomServer::onNewConnection() {
    while (m_server.hasPendingConnections()) {
        auto* s = m_server.nextPendingConnection();
        m_clients.push_back(s);

        connect(s, &QTcpSocket::readyRead, this, &RoomServer::onSocketReadyRead);
        connect(s, &QTcpSocket::disconnected, this, &RoomServer::onSocketDisconnected);

        emit log("Cliente conectado: " + s->peerAddress().toString());
    }
}

void RoomServer::onSocketReadyRead() {
    auto* s = qobject_cast<QTcpSocket*>(sender());
    if (!s) return;

    while (s->canReadLine()) {
        QByteArray line = s->readLine().trimmed();
        if (line.isEmpty()) continue;

        QJsonParseError err{};
        QJsonDocument doc = QJsonDocument::fromJson(line, &err);
        if (err.error != QJsonParseError::NoError || !doc.isObject()) {
            emit log("JSON inválido recebido.");
            continue;
        }

        QJsonObject msg = doc.object();
        emit messageReceived(msg);
        broadcast(msg); // retransmite pra todos (inclui quem enviou)
    }
}

void RoomServer::onSocketDisconnected() {
    auto* s = qobject_cast<QTcpSocket*>(sender());
    if (!s) return;

    m_clients.removeAll(s);
    emit log("Cliente desconectou.");
    s->deleteLater();
}
