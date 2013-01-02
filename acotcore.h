#ifndef ACOTCORE_H
#define ACOTCORE_H

#include <QObject>

class AcotCore : public QObject
{
    Q_OBJECT
public:
    explicit AcotCore(QObject *parent = 0);
    QString GetAppVersion();

signals:
    
public slots:
    
};

#endif // ACOTCORE_H
