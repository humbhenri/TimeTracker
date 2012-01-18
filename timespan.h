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

#ifndef TIMESPAN_H
#define TIMESPAN_H

#include <QDateTime>
#include <QDomDocument>

/**
  * Measure a time span between 2 QDateTime's.
  * A project consist of a collection of TimeSpan's
  */
class TimeSpan : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDateTime start READ getStart WRITE setStart)
    Q_PROPERTY(QDateTime end READ getEnd WRITE setEnd)
public:
    TimeSpan(){}
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
    inline QDateTime getStart() const { return start; }
    inline QDateTime getEnd() const { return end; }
    inline void setStart(QDateTime other) { start = other; }
    inline void setEnd(QDateTime other) { end = other; }
    QDomElement toNode(QDomDocument &d);
    static TimeSpan fromNode(const QDomElement & e);    

private:
    QDateTime end;
    QDateTime start;
};

#endif // TIMESPAN_H
