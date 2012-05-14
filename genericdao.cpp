#include "genericdao.h"
#include "debugutils.h"
#include <QMetaObject>
#include <QMetaProperty>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

namespace DBUtils {

const bool GenericDao::__init = init();

const QString GenericDao::CONNECTION_NAME = "thread";

GenericDao::GenericDao(QObject *parent) :
    QObject(parent)
{
}

bool GenericDao::insertOrUpdate(QObject *dto, QString tableName, QString fkName, QVariant fkValue)
{    
    const QMetaObject *metaObject = dto->metaObject();
    int count = metaObject->propertyCount();
    QStringList names;
    QList<QVariant> values;

    for ( int i=0; i<count; i++ ) {
        QMetaProperty property = metaObject->property(i);
        names << property.name();
        values << dto->property(property.name());
    }
    foreach (QByteArray dynamicProperty, dto->dynamicPropertyNames()) {
        names << QString(dynamicProperty);
        values << dto->property(dynamicProperty.data());
    }

    names.removeOne("objectName");
    values.removeOne(dto->property("objectName"));

    if (!fkName.isEmpty()) {
        names << fkName;
        values << fkValue;
    }

    int valuesCount = values.count();
    QStringList placeHolders;
    for ( int i=0; i<valuesCount; i++) placeHolders << "?";

    QSqlQuery query(QSqlDatabase::database(CONNECTION_NAME));
    query.prepare("REPLACE INTO " + tableName + " (" + names.join(",") + ") " +
                  "VALUES (" + placeHolders.join(",") + ") ");
    foreach (QVariant value, values)
        query.addBindValue(value);
    bool ok = query.exec();
    if (!ok)
        emit error(query.lastError());
    if (ok && !dto->property("id").isValid()) {
        dto->setProperty("id", query.lastInsertId());
    }

    emit finished();
    return ok;
}


bool GenericDao::remove(QObject *dto, QString tableName)
{
    QSqlQuery query(QSqlDatabase::database(CONNECTION_NAME));
    query.prepare("DELETE FROM " + tableName + " WHERE id = ?");
    query.addBindValue(dto->property("id"));
    bool ok = query.exec();
    if (!ok)
        emit error(query.lastError());
    emit finished();
    return ok;
}

QObject * GenericDao::findById(int id, const QMetaObject *metaObject, QString tableName)
{
    QObject * obj = metaObject->newInstance();
    if ( !obj )
        return obj;
    QSqlQuery query(QSqlDatabase::database(CONNECTION_NAME));
    query.prepare("SELECT * FROM " + tableName + " WHERE id = ? ");
    query.addBindValue(QVariant(id));
    bool ok = query.exec();
    if (!ok)
        emit error(query.lastError());
    if ( ok ) {
        while ( query.next() ) {
            QSqlRecord rec = query.record();
            for ( int i=0; i<rec.count(); i++ ) {
                QString field = rec.fieldName(i);
                obj->setProperty(qPrintable(field), rec.value(field));
            }
        }
        emit finished();
        return obj;
    }
    emit finished();
    return 0;
}


QVector<QObject*> GenericDao::select(const QMetaObject *metaObject,QString where, QString tableName)
{
    QVector<QObject*> results;
    QSqlQuery query(QSqlDatabase::database(CONNECTION_NAME));
    bool ok = query.exec("SELECT * FROM " + tableName + " WHERE " + (where.isEmpty()?"1=1":where));
    if ( ok ) {
        while ( query.next() ) {
            QSqlRecord rec = query.record();
            QObject *obj = metaObject->newInstance();
            if ( !obj )
                continue;
            for ( int i=0; i<rec.count(); i++ ) {
                QString field = rec.fieldName(i);
                obj->setProperty(qPrintable(field), rec.value(field));
            }
            results << obj;
        }
    }
    else {
        emit error(query.lastError());
    }

    emit finished();
    return results;
}


bool GenericDao::lastOperationSuccess()
{
    return QSqlDatabase::database(CONNECTION_NAME).lastError().type() == QSqlError::NoError;
}


QString GenericDao::lastError()
{
    return QSqlDatabase::database(CONNECTION_NAME).lastError().text();
}

}
