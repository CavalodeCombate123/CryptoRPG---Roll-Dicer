#ifndef JOINSETUPWINDOW_H
#define JOINSETUPWINDOW_H

#include <QDialog>

namespace Ui {
class JoinSetupWindow;
}

class JoinSetupWindow : public QDialog
{
    Q_OBJECT

public:
    explicit JoinSetupWindow(QWidget *parent = nullptr);
    ~JoinSetupWindow();

private:
    Ui::JoinSetupWindow *ui;
};

#endif // JOINSETUPWINDOW_H
