#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class StartWindow; }
QT_END_NAMESPACE

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::StartWindow *ui;

    QPixmap bgPixmap;     // fundo escolhido (arquivo)
    QString bgPath;       // caminho do arquivo

    void loadBackgroundFromSettings();   // carrega QSettings
    void setBackgroundFile(const QString& path);  // define e salva
    void restoreDefaultBackground();     // limpa QSettings e volta pro padrão

};

#endif // STARTWINDOW_H
