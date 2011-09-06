#ifndef TIMESPAN_H
#define TIMESPAN_H

#include <QDateTime>
#include <QDomDocument>

/**
  * Measure a time span between 2 QDateTime's.
  * A project consist of a collection of TimeSpan's
  */
class TimeSpan
{
public:
    TimeSpan(const TimeSpan & other);
    TimeSpan(const QDateTime&, const QDateTime&);
    QString toString() const;
    static QString toString(int totalSeconds);
    int seconds() const;
    int minutes() const;
    int hours() const;
    int days() const;
    static int SecondsPerMinute;
    static int SecondsPerHour;
    static int SecondsPerDay;
    static int HoursPerDay;
    static int MinutesPerHour;
    static QString DateFormat;
    TimeSpan& operator=(const TimeSpan & other);
    inline QDateTime beginning() const { return start; }
    QDomElement toNode(QDomDocument &d);
    static TimeSpan fromNode(const QDomElement & e);

private:
    QDateTime end;
    QDateTime start;
};

#endif // TIMESPAN_H
