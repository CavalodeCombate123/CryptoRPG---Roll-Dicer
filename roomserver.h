#pragma once
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonObject>
#include <QVector>

class RoomServer : public QObject {
    Q_OBJECT
public:
    explicit RoomServer(QObject* parent = nullptr);

    bool start(quint16 port);
    void stop();
    bool isRunning() const;

    void broadcast(const QJsonObject& msg);

signals:
    void log(const QString& text);
    void messageReceived(const QJsonObject& msg);

private slots:
    void onNewConnection();
    void onSocketReadyRead();
    void onSocketDisconnected();

private:
    QTcpServer m_server;
    QVector<QTcpSocket*> m_clients;
};
