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

#include "project.h"
#include "genericdao.h"
#include "debugutils.h"
#include <QTextStream>
#include <QDomDocument>
#include <QVariant>

const QString Project::TableName = "project";

Project::Project(QObject *parent) :
    QObject(parent), lastModified(QDateTime::currentDateTime()), created(QDateTime::currentDateTime())
{
}

void Project::addTimeTrackingSession(TimeSpan * timeSpan)
{
    timeSpans << timeSpan;
    save();
    emit changed();
}

QString Project::totalTimeSpent() const
{
    int totalSecs = 0;

    QVector<TimeSpan*>::const_iterator it = timeSpans.begin();
    while (it != timeSpans.end()) {
        totalSecs += (*it)->seconds();
        it++;
    }

    return TimeSpan::toString(totalSecs);
}

Project* Project::makeProject(const QString &name, const QString &description)
{
    Project *p = new Project;
    p->setName(name.trimmed());
    p->setDescription(description.trimmed());
    p->save();
    return p;
}

QStringList Project::getProjects()
{
    QStringList names;
    DBUtils::GenericDao dao;
    Project dummy;
    QVector<QObject*> select = dao.select(dummy.metaObject(), "", Project::TableName);
    foreach (QObject* o, select) {
        Project * p = dynamic_cast<Project*>(o);
        names << p->getName();
    }

    return names;
}

Project* Project::getProjectByName(const QString &name)
{
    DBUtils::GenericDao dao;
    Project dummy, *p = 0;
    QVector<QObject*> select = dao.select(dummy.metaObject(), "", Project::TableName);
    foreach (QObject* o, select) {
        p = dynamic_cast<Project*>(o);
        if (p->getName() == name)
            break;
    }
    if (!p) {
        return 0;
    }

    // load timespans
    TimeSpan ts;
    QVector<QObject*> timespans =
            dao.select(ts.metaObject(), "projectId = " + p->property("id").toString(), TimeSpan::TableName);
    foreach (QObject* o, timespans) {
        TimeSpan *timespan = dynamic_cast<TimeSpan*>(o);
        if (timespan) p->timeSpans << timespan;
    }

    return p;
}


bool Project::save()
{
    bool ok = true;
    DBUtils::GenericDao dao;
    ok &= dao.insertOrUpdate(this, Project::TableName);
    foreach (TimeSpan * ts, getTimeSpans()) {
        ok &= ts->save(property("id"));
    }
    return ok;
}


void Project::setName(const QString & newName)
{
    name = newName.trimmed();
    save();
    emit changed();
}


void Project::setDescription(const QString & newDescription)
{
    description = newDescription.trimmed();
    save();
    emit changed();
}
