#ifndef DEBUGUTILS_H
#define DEBUGUTILS_H

#define debugObject(o) qDebug("%s:%d %s", __FILE__,__LINE__, qPrintable(DebugUtils::toString(o)));

#include <QObject>

class DebugUtils : public QObject
{
    Q_OBJECT
public:
    explicit DebugUtils(QObject *parent = 0);
    static QString toString(const QObject* o);
signals:

public slots:

};

#endif // DEBUGUTILS_H
