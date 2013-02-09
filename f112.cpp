#include <QDebug>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QObject>
#include <QTemporaryFile>
#include "f112.h"

F112::F112()
{
}

F112::~F112()
{
    delete excel_;
}


void F112::CreateF112(QStandardItemModel * model, QModelIndex current_index, bool on_print)
{
    CreateBlank(model, current_index);

    model->setItem(current_index.row(), model->columnCount() - 1 , new QStandardItem(QObject::tr("Сформирован")));

    if (on_print)  {

        excel_->setProperty("DisplayAlerts", "0");
        QAxObject* workbooks = excel_->querySubObject( "Workbooks" );
        QAxObject* workbook = workbooks->querySubObject( "Open(const QString&)", new_filename_ );
        QAxObject* sheets = workbook->querySubObject( "Worksheets" );
        QAxObject *sheet1 = sheets->querySubObject( "Item(const QVariant&)", QVariant("page1") );
        QAxObject *sheet2 = sheets->querySubObject( "Item(const QVariant&)", QVariant("page2") );

        sheet1->dynamicCall("PrintOut()");

        int r = QMessageBox::question(0, QObject::tr("Excel"),
                        QObject::tr("Печатать следующую страницу?"),
                        QMessageBox::Yes|QMessageBox::Default,
                        QMessageBox::No|QMessageBox::Escape);
        if (r == QMessageBox::Yes) {

            sheet1->dynamicCall("PrintOut()");
        }
        excel_->dynamicCall("Quit()");

        delete sheet1;
        delete sheet2;
        delete sheets;
        delete workbook;
        delete workbooks;

        model->setItem(current_index.row(), model->columnCount() - 1 , new QStandardItem(QObject::tr("Напечатан")));
    }
}



void F112::CreateBlank(QStandardItemModel *model, QModelIndex current_index)
{
    QTemporaryFile tmp_file;
    tmp_file.open();

    QString tmp_file_path = tmp_file.fileName();
    QString current_dir = QDir::currentPath();

    tmp_file.close();
    qDebug() << "tmp_file_path: " + tmp_file_path;

    tmp_file_path += ".xls";

    QFile f_template(":/bpp/template.xls");
    f_template.copy(QDir::toNativeSeparators(tmp_file_path));

//    try
//    {
        excel_ = new QAxObject( "Excel.Application", 0 );
//    }
//    catch (...)
//    {
//            QMessageBox::information(0, QObject::tr("Ошибка при подключении к MS Excel."), QObject::tr("Проверьте установлен ли Excel в системе."));
//            qDebug() << "Error in new QAxObject( Excel.Application, 0 )";
//    }

    QAxObject* workbooks = excel_->querySubObject( "Workbooks" );
    QAxObject* workbook = workbooks->querySubObject( "Open(const QString&)", tmp_file_path );
    QAxObject* sheets = workbook->querySubObject( "Worksheets" );
    QAxObject *sheet1 = sheets->querySubObject( "Item(const QVariant&)", QVariant("page1") );
    QAxObject *sheet2 = sheets->querySubObject( "Item(const QVariant&)", QVariant("page2") );

    excel_->setProperty("Visible", true );
    excel_->setProperty("DisplayAlerts", "0");

    qDebug() << "data: " << current_index.data();

    QMap<QString, QString> data;
    int current_row = current_index.row();
    for (int i = 0; i < model->columnCount() - 1; i++)
    {
        QStandardItem *cur_item = model->item(current_row, i);

        QString header = model->headerData(i, Qt::Horizontal).toString();

        qDebug() << "header:"  << header << " cur item: " << cur_item->text();

        data[header] = cur_item->text();
    }


    // Заполнение шаблона
    bool ok;
    QString summa = data.value(QObject::tr("Сумма"));
    //summa.replace(".", ",");
    double d_sum = summa.toDouble(&ok);
    int n_sum = int(d_sum);
    int dn_sum = int(100 * (d_sum - n_sum));

    SetCellValue(sheet1, 20, 51, n_sum); // сумма
    SetCellValue(sheet1, 20, 65, QString::number(dn_sum, 'f', 0)); // копейки



    QString who = data.value(QObject::tr("Получатель"));
    QString from = data.value(QObject::tr("От кого(ФИОТБНполн)"));
    QString orgname = data.value(QObject::tr("НазвОрг"));
    QString summa_propisu = data.value(QObject::tr("Сумма прописью"));
    QString org_index = data.value(QObject::tr("ИндексОрг"));
    QString org_address = data.value(QObject::tr("АдресОрг"));
    QString message = data.value(QObject::tr("Сообщение"));

    SetCellValue(sheet1, 23, 30, summa_propisu);

    SetCellValue(sheet1, 25, 35, who);

    QString where = data.value(QObject::tr("Куда"));

    SetCellValue(sheet1, 28, 35, where); // Адрес

    SetCellValue(sheet1, 34, 36, orgname);

    for (int i = 0; i < 6; i++) // Индекс
    {
        SetCellValue(sheet1, 34, 68 + i, QString(org_index[i]));
    }

    SetCellValue(sheet1, 63, 30, org_address);

    int i = 0;
    bool at_end = false;

    // Разбивка по строкам сообщения
    while ((i < 37) && (at_end == false))
    {
        at_end = (i == message.length() - 1);

        SetCellValue(sheet1, 69, 37 + i, QString(message[i]));
        i++;
    }

    int j = i;
    i = 0;
    while (i < message.length() - 1)
    {
        SetCellValue(sheet1, 73, 31 + i, QString(message[j]));
        i++;  j++;
    }

    // Страница 2

    SetCellValue(sheet2, 13, 107, n_sum); // сумма
    SetCellValue(sheet2, 13, 120, QString::number(dn_sum, 'f', 0)); // копейки

    // от кого
    int surname_idx = from.indexOf(" ");
    QString surname = from.left(surname_idx);
    SetCellValue(sheet2, 17, 100, surname);
    SetCellValue(sheet2, 21, 90, from.right(from.length() - surname_idx));

    SetCellValue(sheet2, 33, 14, summa_propisu);

    // кому
    surname_idx = who.indexOf(" ");
    surname = who.left(surname_idx);
    SetCellValue(sheet2, 38, 12, surname);
    SetCellValue(sheet2, 42, 4, who.right(who.length() - surname_idx));


    // адрес отправителя
    SetCellValue(sheet2, 36, 111, org_index);

    SetCellValue(sheet2, 39, 90, org_address.left(20));
    if (org_address.length() > 20)
        SetCellValue(sheet2, 42, 90, org_address.right(org_address.length() - 20));

    //
    new_filename_ = QDir::toNativeSeparators(current_dir + "/" + from + ".xls");
    workbook->querySubObject("SaveAs (const QString&)", new_filename_);

    int msg_length = message.length();

    SetCellValue(sheet2, 60, 103, message.left(20));
    if (msg_length > 20)
        SetCellValue(sheet2, 62, 90, message.mid(20, 30));
    if (msg_length > 50)
        SetCellValue(sheet2, 65, 90, message.mid(50, 30));
    if (msg_length > 80)
        SetCellValue(sheet2, 68, 90, message.mid(80, 30));
    if (msg_length > 110)
        SetCellValue(sheet2, 73, 90, message.mid(110, 30));

        //временно
    //workbook->dynamicCall("Close (Boolean)", true);
    //excel_->dynamicCall("Quit (void)");


    delete sheet1;
    delete sheet2;
    delete sheets;
    delete workbook;
    delete workbooks;


}

void F112::SetCellValue(QAxObject *sheet, int row, int col, QVariant value)
{
    // получение указателя на ячейку [row][col] ((!)нумерация с единицы)
    QAxObject* cell = sheet->querySubObject("Cells(QVariant,QVariant)", row, col);
    // вставка значения переменной data (любой тип, приводимый к QVariant) в полученную ячейку
    cell->setProperty("Value", QVariant(value));
    // освобождение памяти
    delete cell;
}
