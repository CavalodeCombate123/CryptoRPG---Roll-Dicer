#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSet>
#include <QPixmap>
#include <QString>

#include "diceengine.h"
#include "roomserver.h"
#include "roomclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setNick(const QString& nick);
    void startHost(quint16 port);
    void startJoin(const QString& ip, quint16 port);
    void startSoloMode();

private:
    Ui::MainWindow *ui = nullptr;

    RoomServer* server = nullptr;
    RoomClient* client = nullptr;
    QString nickname = "Player";

    DiceEngine engine;

    QSet<QString> players;

    QPixmap bgPixmap;
    QString bgPath;

    void loadBackground(const QString& path);

    enum class GameMode { Solo, OnlineHost, OnlineClient };
    GameMode mode = GameMode::Solo;
    void applySoloUi();
    void applyOnlineUi();
    void leaveRoom();


protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif // MAINWINDOW_H
