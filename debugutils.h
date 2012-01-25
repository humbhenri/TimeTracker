#ifndef DEBUGUTILS_H
#define DEBUGUTILS_H

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
