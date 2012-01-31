#ifndef GENERICDAO_H
#define GENERICDAO_H

#include <QObject>
#include <QMetaObject>
#include <QVector>

namespace DBUtils {

class GenericDao : public QObject
{
    Q_OBJECT
public:
    explicit GenericDao(QObject *parent = 0);
    bool insert(QObject *dto, QString tableName);
    bool insert(QObject *dto, QString tableName, QString fkName, QVariant fkValue);
    bool remove(QObject *dto, QString tableName);
    bool update(QObject *dto, QString tableName);
    QObject* findById(int id, const QMetaObject *metaObject, QString tableName);
    QVector<QObject*> select(const QMetaObject *metaObject, QString where, QString tableName);
signals:

public slots:

};

}

#endif // GENERICDAO_H
