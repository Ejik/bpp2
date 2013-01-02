#include "mainwindow.h"
#include <QDebug>
#include <QApplication>
#include <QTextCodec>


int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);

    QApplication a(argc, argv);
    // Setting the Application version
    a.setApplicationVersion(APP_VERSION);

    MainWindow w;

    w.show();


    return a.exec();
}
