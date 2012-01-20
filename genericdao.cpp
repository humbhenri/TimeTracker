#include "genericdao.h"
#include <QMetaObject>
#include <QMetaProperty>
#include <QStringList>
#include <QtSql/QSqlQuery>
#include <QSqlError>
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
    values.removeOne(dto->property("objectName"));;

    QStringList sets;
    for( int i=0; i < values.count(); i++ ) {
//        sets << QString(" :column") + QString::number(i) + " = :param" + QString::number(i);
        sets << " ? = ? ";
    }
    QSqlQuery query(QSqlDatabase::database());
//    query.prepare("UPDATE :tableName SET " + sets.join(",") + " WHERE id = :id ");
    query.prepare("update "+ tableName +" set " + sets.join(",") + " where id = " + dto->property("id").toString());
    qDebug() << query.lastError().text();
//    query.bindValue(":tableName", tableName);
//    query.addBindValue(tableName);
    for ( int i=0; i < values.count(); i++) {
//        query.bindValue(":column" + QString::number(i), names.at(i));
//        query.bindValue(":param" + QString::number(i), values.at(i));
        query.addBindValue(names.at(i));
        query.addBindValue(values.at(i));
    }
//    query.bindValue(":id", dto->property("id"));
//    query.addBindValue(dto->property("id"));

        bool ok = query.exec();

    qDebug() << "Bound Values: " << query.boundValues();

    qDebug() << query.lastQuery();

    qDebug() << query.lastError().text();

    return ok;
}

}
