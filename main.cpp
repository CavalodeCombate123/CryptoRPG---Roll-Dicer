#include <QApplication>
#include "startwindow.h"
#include "theme.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    applyAppTheme();

    StartWindow w;
    w.show();
    return a.exec();
}
