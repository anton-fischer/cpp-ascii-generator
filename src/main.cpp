#include "../include/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon(":/images/resources/ascii.png"));

    MainWindow w;
    w.setWindowTitle("Ascii-Art-Generator");
    w.show();
    return a.exec();
}
