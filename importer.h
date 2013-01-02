#ifndef IMPORTER_H
#define IMPORTER_H

#include <QObject>

class Importer : public QObject
{
    Q_OBJECT
public:
    explicit Importer(QObject *parent = 0);
    void ImportData();

signals:
    
public slots:

private:

    static const QString separator() { return "|" ; }
    static const QString datafilename() { return "ALIMEXL.LSB"; }
};

#endif // IMPORTER_H
