#include "mainwindow.h"
#include <QDebug>
#include <QApplication>
#include <QStandardItemModel>
#include <QTextCodec>
#include "importer.h"

int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);

    QApplication a(argc, argv);
    // Setting the Application version
    a.setApplicationVersion(APP_VERSION);

    Importer importer;
    QStandardItemModel *model = importer.ImportData();


    MainWindow w;
    w.SetModel(model);
    w.show();

    return a.exec();
}
