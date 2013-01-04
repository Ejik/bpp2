#ifndef F112_H
#define F112_H

#include <QAxObject>
#include <QModelIndex>
#include <QStandardItemModel>


class F112
{
public:
    F112();
    ~F112();
    void CreateF112(QStandardItemModel * model, QModelIndex current_index, bool on_printer);

private:
    void CreateBlank(QStandardItemModel * model, QModelIndex current_index);
    void SetCellValue(QAxObject *sheet, int row, int col, QVariant value);

    QAxObject* excel_;
    QString new_filename_;
};

#endif // F112_H

