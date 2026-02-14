#pragma once
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>

inline QByteArray packJsonLine(const QJsonObject& obj) {
    QJsonDocument doc(obj);
    QByteArray line = doc.toJson(QJsonDocument::Compact);
    line.append('\n');
    return line;
}
