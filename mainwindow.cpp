#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile f(":/style/style.qss");
    if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        this->setStyleSheet(QString::fromUtf8(f.readAll()));
    }

    QFont font;
    font.setPointSize(14);

    ui->inputExpr->setFont(font);
    ui->outputBox->setFont(font);
    ui->historyList->setFont(font);

    QFont btnFont;
    btnFont.setPointSize(16);
    btnFont.setBold(true);
    ui->btnRoll->setFont(btnFont);

    connect(ui->btnRoll, &QPushButton::clicked, this, [this]() {
        const std::string expr = ui->inputExpr->text().toStdString();

        if (expr.empty()) {
            ui->outputBox->setPlainText("Digite uma expressao (ex: 3d8+2d10+5).");
            return;
        }

        try {
            RollResult r = engine.rollExpression(expr);

            // Mostra detalhes + total
            QString out = QString::fromStdString(r.detailsText)
                          + "\nTotal: " + QString::number(r.total);

            ui->outputBox->setPlainText(out);

            // Histórico com dados + total
            ui->historyList->addItem(QString::fromStdString(r.historyLine));
        } catch (...) {
            ui->outputBox->setPlainText("Expressao invalida. Ex: 3d8+2d10+5 ou 2d20-3");
        }
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}
