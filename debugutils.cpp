#include "debugutils.h"
#include <QMetaObject>
#include <QMetaProperty>
#include <QVariant>
#include <QByteArray>

DebugUtils::DebugUtils(QObject *parent) :
    QObject(parent)
{
}

QString DebugUtils::toString(const QObject *o)
{
    QString result("\nDumping object\n");
    if ( !o )
        return result;
    const QMetaObject *meta = o->metaObject();
    for( int i=0; i<meta->propertyCount(); i++ ) {
        const char * propertyName = meta->property(i).name();
        QVariant value = o->property(propertyName);
        result += "\t" + QString(propertyName) + ": " + value.toString() + "\n";
    }
    foreach(QByteArray dynamicPropery, o->dynamicPropertyNames()) {
        result += "\t" + QString(dynamicPropery) + ": " + o->property(dynamicPropery.data()).toString() + "\n";
    }

    return result;
}
