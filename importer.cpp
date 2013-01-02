#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QTextStream>
#include "importer.h"


Importer::Importer(QObject *parent) :
    QObject(parent)
{
}

void Importer::ImportData()
{
    QString current_path = QDir::currentPath() +  "//" + datafilename();
    QFile file(QDir::toNativeSeparators(current_path));
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, tr("Ошибка"), file.errorString());
        qDebug() << "Error in open file: " + file.errorString();
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(separator());

        //model->appendRow(fields);
    }

    file.close();
}
