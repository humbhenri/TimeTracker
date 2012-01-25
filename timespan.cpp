/*Copyright 2011 Humberto Pinheiro. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are
permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice, this list of
      conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice, this list
      of conditions and the following disclaimer in the documentation and/or other materials
      provided with the distribution.

THIS SOFTWARE IS PROVIDED BY Humberto Pinheiro ''AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Humberto Pinheiro OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those of the
authors and should not be interpreted as representing official policies, either expressed
or implied, of Humberto Pinheiro.*/

#include "timespan.h"
#include "debugutils.h"
#include <QVariant>

int TimeSpan::SecondsPerMinute = 60;
int TimeSpan::SecondsPerHour = 3600;
int TimeSpan::SecondsPerDay = 86400;
int TimeSpan::HoursPerDay = 24;
int TimeSpan::MinutesPerHour = 60;
QString TimeSpan::DateFormat = "MMM dd yyyy hh:mm:ss";

QString buildTimeRepresentationHelper(int days, int hours, int minutes)
{
    QString daysStr("");
    QString hoursStr("");
    QString minutesStr("");

    if (days != 0)
        daysStr = QString("%1 days ").arg(QString::number(days));
    if (hours != 0)
        hoursStr = QString("%1 hours ").arg(QString::number(hours));
    if (minutes != 0)
        minutesStr = QString("%1 minutes ").arg(QString::number(minutes));
    return daysStr + hoursStr + minutesStr;
}

TimeSpan::TimeSpan(const QDateTime& date1, const QDateTime& date2)
{
    int seconds_span = date1.secsTo(date2);
    if (seconds_span > 0) {
        end = date2;
        start = date1;
    }
    else {
        end = date1;
        start = date2;
    }
}

TimeSpan::TimeSpan(const TimeSpan &other)
{
    end = other.end;
    start = other.start;
}

TimeSpan::TimeSpan(const QObject &obj)
{
    end = obj.property("end").toDateTime();
    start = obj.property("start").toDateTime();
    setProperty("id", obj.property("id"));
}

QString TimeSpan::toString() const
{
    int seconds_span = start.secsTo(end);
    int ndays = seconds_span / TimeSpan::SecondsPerDay;
    int minutes = (seconds_span / TimeSpan::SecondsPerMinute) % TimeSpan::MinutesPerHour;
    int hours = (seconds_span / TimeSpan::SecondsPerHour) % TimeSpan::HoursPerDay;

    QString string = buildTimeRepresentationHelper(ndays, hours, minutes);
    if (string.isEmpty())
        return QString("--");
    else
        return string;
}

QString TimeSpan::toString(int totalSeconds)
{
    int ndays = totalSeconds / TimeSpan::SecondsPerDay;
    int minutes = (totalSeconds / TimeSpan::SecondsPerMinute) % TimeSpan::MinutesPerHour;
    int hours = (totalSeconds / TimeSpan::SecondsPerHour) % TimeSpan::HoursPerDay;

    QString string = buildTimeRepresentationHelper(ndays, hours, minutes);
    if (string.isEmpty())
        return QString("--");
    else
        return string;
}

int TimeSpan::seconds() const
{
    int seconds_span = start.secsTo(end);
    return seconds_span;
}

int TimeSpan::minutes() const
{
    int seconds_span = start.secsTo(end);
    return seconds_span / TimeSpan::SecondsPerMinute;
}

int TimeSpan::hours() const
{
    int seconds_span = start.secsTo(end);
    return seconds_span /TimeSpan::SecondsPerHour ;
}

int TimeSpan::days() const
{
    return start.daysTo(end);
}

TimeSpan& TimeSpan::operator =(const TimeSpan & other)
{
    end = other.end;
    start = other.start;
    return *this;
}

QDomElement TimeSpan::toNode(QDomDocument & d)
{
    QDomElement node = d.createElement("timeSpan");
    node.setAttribute("start", start.toString(DateFormat));
    node.setAttribute("end", end.toString(DateFormat));
    return node;
}

TimeSpan TimeSpan::fromNode(const QDomElement &e)
{
    if (!e.isNull() && e.tagName() == "timeSpan") {
        return TimeSpan(QDateTime::fromString(e.attribute("start", ""), DateFormat),
                        QDateTime::fromString(e.attribute("end", ""), DateFormat));
    }
    return TimeSpan(QDateTime::currentDateTime(), QDateTime::currentDateTime());
}

bool TimeSpan::operator ==(const TimeSpan &other)
{
    qDebug(qPrintable(DebugUtils::toString(this)));
    qDebug(qPrintable(DebugUtils::toString(&other)));
    return this->start == other.start &&
            this->end == other.end;
}
