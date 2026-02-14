#pragma once
#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>

class RoomClient : public QObject {
    Q_OBJECT
public:
    explicit RoomClient(QObject* parent = nullptr);

    void connectTo(const QString& host, quint16 port);
    void disconnect();
    bool isConnected() const;

    void send(const QJsonObject& msg);

signals:
    void connected();
    void disconnected();
    void error(const QString& text);
    void messageReceived(const QJsonObject& msg);

private slots:
    void onReadyRead();

private:
    QTcpSocket m_socket;
};
