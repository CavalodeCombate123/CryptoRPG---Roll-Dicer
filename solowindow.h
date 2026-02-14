#ifndef SOLOWINDOW_H
#define SOLOWINDOW_H

#include <QMainWindow>

namespace Ui {
class SoloWindow;
}

class SoloWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SoloWindow(QWidget *parent = nullptr);
    ~SoloWindow();

private:
    Ui::SoloWindow *ui;
};

#endif // SOLOWINDOW_H
