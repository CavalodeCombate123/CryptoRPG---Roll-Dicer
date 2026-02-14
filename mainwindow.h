#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "roomserver.h"
#include "roomclient.h"
#include <QMainWindow>
#include "diceengine.h"
#include <QSet>
#include <QStringList>
#include <QPixmap>
#include <QSettings>



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    RoomServer* server = nullptr;
    RoomClient* client = nullptr;
    QString nickname = "Player";
    Ui::MainWindow *ui;
    DiceEngine engine;
    QSet<QString> players;
    QPixmap bgPixmap;
    QString bgPath;

    void loadBackground(const QString& path);

protected:
    void paintEvent(QPaintEvent* event) override;

};
#endif // MAINWINDOW_H
