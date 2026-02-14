#include "roomclient.h"
#include "roomprotocol.h"
#include <QJsonDocument>

RoomClient::RoomClient(QObject* parent) : QObject(parent) {
    connect(&m_socket, &QTcpSocket::connected, this, &RoomClient::connected);
    connect(&m_socket, &QTcpSocket::disconnected, this, &RoomClient::disconnected);
    connect(&m_socket, &QTcpSocket::readyRead, this, &RoomClient::onReadyRead);

    connect(&m_socket, &QTcpSocket::errorOccurred, this, [this](QAbstractSocket::SocketError) {
        emit error(m_socket.errorString());
    });
}

void RoomClient::connectTo(const QString& host, quint16 port) {
    m_socket.connectToHost(host, port);
}

void RoomClient::disconnect() { m_socket.disconnectFromHost(); }
bool RoomClient::isConnected() const { return m_socket.state() == QAbstractSocket::ConnectedState; }

void RoomClient::send(const QJsonObject& msg) {
    if (!isConnected()) return;
    m_socket.write(packJsonLine(msg));
}

void RoomClient::onReadyRead() {
    while (m_socket.canReadLine()) {
        QByteArray line = m_socket.readLine().trimmed();
        if (line.isEmpty()) continue;

        QJsonParseError err{};
        QJsonDocument doc = QJsonDocument::fromJson(line, &err);
        if (err.error != QJsonParseError::NoError || !doc.isObject()) continue;

        emit messageReceived(doc.object());
    }
}
