#include "genericdao.h"
#include <QMetaObject>
#include <QMetaProperty>
#include <QStringList>
#include <QtSql/QSqlQuery>
#include <QSqlError>

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
    // remove objectName property
    names.removeOne("objectName");
    values.removeOne(dto->property("objectName"));

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
    // remove objectName property
    names.removeFirst();
    values.removeFirst();

    int valuesCount = values.count();

    QSqlQuery query;
    QString sql = QString("UPDATE ? SET ");
    QStringList sets;
    for( int i=0; i < valuesCount; i++ ) sets << QString("?=?");
    sql.append(sets.join(",")).append(" WHERE id = ?");
    query.prepare(sql);
    query.addBindValue(tableName);
    for ( int i=0; i < valuesCount; i++) {
        query.addBindValue(names.at(i));
        query.addBindValue(values.at(i));
    }
    query.addBindValue(dto->property("id"));
    bool ok = query.exec();
    qDebug(qPrintable(query.lastError().text()));
    qDebug(qPrintable(query.executedQuery()));
    qDebug("%d", values.count());
    return ok;
}

}
