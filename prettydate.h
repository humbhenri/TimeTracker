#ifndef PRETTYDATE_H
#define PRETTYDATE_H

#include <QDateTime>

class PrettyDate
{
public:
    static QString prettify(QDateTime);
    static const QString JUST_NOW;
    static const QString MINUTE_AGO;
    static const QString MINUTES_AGO;
    static const QString HOUR_AGO;
    static const QString HOURS_AGO;
private:
    PrettyDate(){}
};

#endif // PRETTYDATE_H
