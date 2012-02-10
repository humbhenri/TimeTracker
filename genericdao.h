#ifndef GENERICDAO_H
#define GENERICDAO_H

#include <QObject>
#include <QMetaObject>
#include <QVector>
#include <QVariant>

namespace DBUtils {

class GenericDao : public QObject
{
    Q_OBJECT
public:
    explicit GenericDao(QObject *parent = 0);
    bool insertOrUpdate(QObject *dto, QString tableName, QString fkName="", QVariant fkValue=QVariant());
    bool remove(QObject *dto, QString tableName);
    QObject* findById(int id, const QMetaObject *metaObject, QString tableName);
    QVector<QObject*> select(const QMetaObject *metaObject, QString where, QString tableName);
    bool lastOperationSuccess();    
signals:

public slots:

};

}

#endif // GENERICDAO_H
