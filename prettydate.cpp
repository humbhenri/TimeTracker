#include "prettydate.h"

const QString PrettyDate::JUST_NOW = "Just now ";
const QString PrettyDate::MINUTE_AGO = "Minute ago ";
const QString PrettyDate::MINUTES_AGO = " minutes ago ";
const QString PrettyDate::HOUR_AGO = "Hour ago ";
const QString PrettyDate::HOURS_AGO = " hours ago ";

QString PrettyDate::prettify(QDateTime aDateTime)
{
    int secsDiff = aDateTime.secsTo(QDateTime::currentDateTime());
    if(secsDiff < 60)
        return JUST_NOW;
    else if (secsDiff < 120)
        return MINUTE_AGO;
    else if (secsDiff < 3600)
        return QString::number(secsDiff/60) + MINUTES_AGO;
    else if (secsDiff < 7200)
        return HOUR_AGO;
    else if (secsDiff < 86400)
        return QString::number(secsDiff/3600) + HOURS_AGO;
    return aDateTime.toString("dd/MM/yyyy hh:mm:ss");
}
