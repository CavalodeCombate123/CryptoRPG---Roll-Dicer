#pragma once
#include <QApplication>
#include <QFile>

inline void applyAppTheme()
{
    QFile f(":/style/style.qss");
    if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qApp->setStyleSheet(QString::fromUtf8(f.readAll()));
    }
}
