#include <QDebug>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QStandardItem>
#include <QTextCodec>
#include <QTextStream>
#include "importer.h"


Importer::Importer(QObject *parent) :
    QObject(parent)
{
}

QStandardItemModel* Importer::ImportData()
{
    QString current_path = QDir::currentPath() +  "//" + datafilename();
    QFile file(QDir::toNativeSeparators(current_path));
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, tr("Ошибка"), file.errorString());
        qDebug() << "Error in open file: " + file.errorString();
    }

    QTextStream in(&file);
    in.setCodec(QTextCodec::codecForName("IBM 866"));

    QString line = in.readLine();
    QStringList fields = line.split(separator());

    QStandardItemModel *model = new QStandardItemModel(0, fields.count()+1);
    model->setHorizontalHeaderLabels(fields);

    // Заменяем заголовки столбцов
    for (int i = 0; i < model->columnCount() - 1; i++)
    {
        QStandardItem *item = model->horizontalHeaderItem(i);
        QString item_text = item->text();

        if (item_text.compare(tr("ФИОТБН")) == 0) {
            item->setText(tr("Отправитель"));
        } else if (item_text.compare(tr("Кому")) == 0) {
            item->setText(tr("Получатель"));
        }
    }
    int last_col_idx = model->columnCount() - 1;
    model->setHorizontalHeaderItem(last_col_idx, new QStandardItem(tr("Состояние")));

    model->horizontalHeaderItem(last_col_idx)->setText(tr("Состояние"));

//    model->setHorizontalHeaderItem(0, new QStandardItem(tr("ТБН")));
//    model->setHorizontalHeaderItem(1, new QStandardItem(tr("Отправитель")));
//    model->setHorizontalHeaderItem(4, new QStandardItem(tr("Получатель")));
//    model->setHorizontalHeaderItem(12, new QStandardItem(tr("Состояние")));

    while(!in.atEnd())
    {
        QString line = in.readLine();
        QStringList fields = line.split(separator());

        QStringListIterator it(fields);
        QList<QStandardItem *> data;
        while (it.hasNext())
        {
            data << new QStandardItem(it.next());
        }

        model->appendRow(data);
    }

    file.close();

    return model;
}
