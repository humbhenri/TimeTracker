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

#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include <QVector>
#include <QDomDocument>
#include <QDateTime>
#include "timespan.h"

class Project : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName)
    Q_PROPERTY(QString description READ getDescription WRITE setDescription)
public:    
    Q_INVOKABLE Project(QObject *parent = 0);
    inline void setName(const QString & newName) { name = newName.trimmed(); emit changed();}
    inline QString getName() const { return name; }
    inline void setDescription(const QString & newDescription) { description = newDescription.trimmed(); emit changed();}
    inline QString getDescription() const { return description; }
    void addTimeTrackingSession(TimeSpan * timeSpan);
    inline QVector<TimeSpan*> getTimeSpans() const { return timeSpans; }
    QString totalTimeSpent() const;    
    static Project* makeProject(const QString & name, const QString & description);
    static QList<Project*> getProjects();
    static Project* getProjectByName(const QString & name);
    static QDomElement getAllProjectsAsDomElement(QDomDocument &d);
    static void createProjectsFromDomElement(const QDomElement &d);
    static bool save();
    static bool restore();
    bool saveTimespans();
    static const QString TableName;
signals:
    void changed();

public slots:

private:    
    QString name;
    QString description;
    QDateTime lastModified;
    QDateTime created;
    QVector<TimeSpan*> timeSpans;
    static QList<Project*> projects;
};

#endif // PROJECT_H
