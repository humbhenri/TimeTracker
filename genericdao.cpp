#include "genericdao.h"
#include <QMetaObject>
#include <QMetaProperty>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

namespace DBUtils {

GenericDao::GenericDao(QObject *parent) :
    QObject(parent)
{
}

bool GenericDao::insert(QObject *dto, QString tableName)
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
    names.removeOne("objectName");
    values.removeOne(dto->property("objectName"));
    names.removeOne("id");
    values.removeOne(dto->property("id"));

    int valuesCount = values.count();
    QStringList placeHolders;
    for ( int i=0; i<valuesCount; i++) placeHolders << "?";

    QSqlQuery query;
    query.prepare("INSERT INTO " + tableName + " (" + names.join(",") + ") " +
                  "VALUES (" + placeHolders.join(",") + ") ");
    foreach (QVariant value, values)
        query.addBindValue(value);
    bool ok = query.exec();
    if (ok)
        dto->setProperty("id", query.lastInsertId());

    return ok;
}


bool GenericDao::insert(QObject *dto, QString tableName, QString fkName, QVariant fkValue)
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
    names.removeOne("objectName");
    values.removeOne(dto->property("objectName"));
    names.removeOne("id");
    values.removeOne(dto->property("id"));

    names << fkName;
    values << fkValue;

    int valuesCount = values.count();
    QStringList placeHolders;
    for ( int i=0; i<valuesCount; i++) placeHolders << "?";

    QSqlQuery query;
    query.prepare("INSERT INTO " + tableName + " (" + names.join(",") + ") " +
                  "VALUES (" + placeHolders.join(",") + ") ");
    foreach (QVariant value, values)
        query.addBindValue(value);
    bool ok = query.exec();
    if (ok)
        dto->setProperty("id", query.lastInsertId());
    return ok;
}


bool GenericDao::remove(QObject *dto, QString tableName)
{
    QSqlQuery query;
    query.prepare("DELETE FROM " + tableName + " WHERE id = ?");
    query.addBindValue(dto->property("id"));
    bool ok = query.exec();
    return ok;
}

bool GenericDao::update(QObject *dto, QString tableName)
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
    names.removeOne("objectName");
    values.removeOne(dto->property("objectName"));
    names.removeOne("id");
    values.removeOne(dto->property("id"));

    QString sql("UPDATE " + tableName + " SET ");
    QStringList sets;
    for ( int i=0; i<values.count(); i++ ) {
        sets << names.at(i) + " = ?";
    }
    sql += sets.join(",") + " WHERE id = " + dto->property("id").toString();
    QSqlQuery query(QSqlDatabase::database());
    query.prepare(sql);
    for ( int i=0; i<values.count(); i++ ) {
        query.addBindValue(values.at(i));
    }
    bool ok = query.exec();
    return ok;

}


QObject * GenericDao::findById(int id, const QMetaObject *metaObject, QString tableName)
{
    QObject * obj = metaObject->newInstance();
    if ( !obj )
        return obj;
    QSqlQuery query(QSqlDatabase::database());
    query.prepare("SELECT * FROM " + tableName + " WHERE id = ? ");
    query.addBindValue(QVariant(id));
    bool ok = query.exec();
    if ( ok ) {
        while ( query.next() ) {
            QSqlRecord rec = query.record();
            for ( int i=0; i<rec.count(); i++ ) {
                QString field = rec.fieldName(i);
                obj->setProperty(qPrintable(field), rec.value(field));
            }
        }
        return obj;
    }
    else {
        return 0;
    }
}


QVector<QObject*> GenericDao::select(const QMetaObject *metaObject,QString where, QString tableName)
{
    QVector<QObject*> results;
    QSqlQuery query(QSqlDatabase::database());
    query.prepare("SELECT * FROM " + tableName + " WHERE " + (where.isEmpty()?"1=1":where));
    bool ok = query.exec();
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
    return results;
}


}
