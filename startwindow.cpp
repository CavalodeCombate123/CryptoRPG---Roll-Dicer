#include "startwindow.h"
#include "ui_startwindow.h"

#include "hostsetupwindow.h"
#include "joinsetupwindow.h"
#include "mainwindow.h"

#include <QSettings>
#include <QFileDialog>
#include <QStandardPaths>
#include <QPainter>
#include <QFile>
#include <QFileInfo>

StartWindow::StartWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartWindow)
{
    ui->setupUi(this);

    // Aplica o style.qss também no StartWindow
    QFile f(":/style/style.qss");
    if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        this->setStyleSheet(QString::fromUtf8(f.readAll()));
    }

    // Carrega background salvo (se houver)
    loadBackgroundFromSettings();

    // BACKGROUND: escolher imagem
    connect(ui->btnBg, &QPushButton::clicked, this, [this](){
        QString file = QFileDialog::getOpenFileName(
            this,
            "Escolher background",
            QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
            "Imagens (*.png *.jpg *.jpeg)"
            );

        if (file.isEmpty()) return;
        if (!QFileInfo::exists(file)) return;

        setBackgroundFile(file); // salva no QSettings e redesenha
    });

    // RESTAURAR: volta pro padrão (remove do QSettings)
    connect(ui->btnRestoreBg, &QPushButton::clicked, this, [this](){
        restoreDefaultBackground();
    });

    // JOGAR (SOLO)
    connect(ui->btnSolo, &QPushButton::clicked, this, [this](){
        auto *room = new MainWindow();
        room->setAttribute(Qt::WA_DeleteOnClose);
        room->show();
        room->startSoloMode();

        this->hide();

        connect(room, &QObject::destroyed, this, [this](){
            this->show();
            loadBackgroundFromSettings(); // atualiza menu ao voltar
        });
    });

    // HOST
    connect(ui->btnHost, &QPushButton::clicked, this, [this](){
        HostSetupWindow dlg(this);
        if (dlg.exec() == QDialog::Accepted) {
            this->hide(); // a sala reabre o Start quando fechar (seu connect já faz isso)
        }
    });

    // ENTRAR
    connect(ui->btnJoin, &QPushButton::clicked, this, [this](){
        JoinSetupWindow dlg(this);
        if (dlg.exec() == QDialog::Accepted) {
            this->hide();
        }
    });
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::loadBackgroundFromSettings()
{
    QSettings s("CryptoRPG", "CryptoRPG");
    const QString saved = s.value("backgroundPath", "").toString();

    if (!saved.isEmpty() && QFileInfo::exists(saved)) {
        QPixmap px(saved);
        if (!px.isNull()) {
            bgPixmap = px;
            bgPath = saved;
            update();
            return;
        }
    }

    // sem fundo salvo (ou inválido)
    bgPixmap = QPixmap();
    bgPath.clear();
    update();
}

void StartWindow::setBackgroundFile(const QString& path)
{
    QPixmap px(path);
    if (px.isNull()) return;

    bgPixmap = px;
    bgPath = path;

    QSettings s("CryptoRPG", "CryptoRPG");
    s.setValue("backgroundPath", bgPath);

    update();
}

void StartWindow::restoreDefaultBackground()
{
    bgPixmap = QPixmap();
    bgPath.clear();

    QSettings s("CryptoRPG", "CryptoRPG");
    s.remove("backgroundPath");

    update();
}

void StartWindow::paintEvent(QPaintEvent *event)
{
    // Se usuário escolheu imagem: desenha ela
    if (!bgPixmap.isNull()) {
        QPainter p(this);
        p.setRenderHint(QPainter::SmoothPixmapTransform, true);

        QRect target = rect();
        QPixmap scaled = bgPixmap.scaled(
            target.size(),
            Qt::KeepAspectRatioByExpanding,
            Qt::SmoothTransformation
            );

        int x = (scaled.width()  - target.width())  / 2;
        int y = (scaled.height() - target.height()) / 2;
        QRect source(x, y, target.width(), target.height());

        p.drawPixmap(target, scaled, source);
    }

    QMainWindow::paintEvent(event);
}
