#ifndef HOSTSETUPWINDOW_H
#define HOSTSETUPWINDOW_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class HostSetupWindow;
}

class HostSetupWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HostSetupWindow(QWidget *parent = nullptr);
    ~HostSetupWindow();

private:
    Ui::HostSetupWindow *ui;

    QStringList localIPv4List() const;
    void refreshHostInfoLabel();
};

#endif // HOSTSETUPWINDOW_H
