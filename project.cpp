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
#include <QTextStream>
#include <QDomDocument>
#include <QVariant>

QList<Project*> Project::projects;

const QString Project::TableName = "project";

Project::Project(QObject *parent) :
    QObject(parent)
{
    Project::projects.push_back(this);
}

void Project::addTimeTrackingSession(const TimeSpan &timeSpan)
{
    timeSpans.push_back(timeSpan);
    emit changed();
}

QString Project::totalTimeSpent() const
{
    int totalSecs = 0;

    QList<TimeSpan>::const_iterator it = timeSpans.begin();
    while (it != timeSpans.end()) {
        totalSecs += (*it).seconds();
        it++;
    }

    return TimeSpan::toString(totalSecs);
}

Project* Project::makeProject(const QString &name, const QString &description)
{
    Project *p = new Project;
    p->setName(name.trimmed());
    p->setDescription(description.trimmed());
    Project::projects.push_back(p);
    return p;
}

QList<Project*> Project::getProjects()
{
    return Project::projects;
}

Project* Project::getProjectByName(const QString &name)
{
    QList<Project*>::iterator it = Project::projects.begin();
    while (it != projects.end()) {
        if ((*it)->getName() == name)
            return *it;
        it++;
    }
    return 0;
}

QDomElement Project::getAllProjectsAsDomElement(QDomDocument & d)
{
    QDomElement root = d.createElement("projects");
    d.appendChild(root);

    QList<Project*>::iterator it = projects.begin();
    for (; it != projects.end(); it++) {
        QDomElement p = d.createElement("project");
        p.setAttribute("name", (*it)->getName());
        p.setAttribute("description", (*it)->getDescription());
        QList<TimeSpan> timeSpans = (*it)->getTimeSpans();
        QList<TimeSpan>::iterator tsIt = timeSpans.begin();
        for (; tsIt != timeSpans.end(); tsIt++) {
            p.appendChild((*tsIt).toNode(d));
        }
        root.appendChild(p);
    }

    return root;
}

void Project::createProjectsFromDomElement(const QDomElement &e)
{
    if (!e.isNull() && e.tagName() == "projects") {
        QDomNode n = e.firstChild();
        while (!n.isNull()) {
            QDomElement p = n.toElement();
            if (!p.isNull() && p.tagName() == "project") {
                Project *project = makeProject(
                    p.attribute("name", ""),
                    p.attribute("description", "")
                );
                QDomNode ts = p.firstChild();
                while (!ts.isNull()){
                    TimeSpan timeSpan = TimeSpan::fromNode(ts.toElement());
                    if (timeSpan.minutes() > 0)
                        project->addTimeTrackingSession(timeSpan);
                    ts = ts.nextSibling();
                }
            }
            n = n.nextSibling();
        }
    }
}

bool Project::save()
{    
    bool ok = true;
    DBUtils::GenericDao dao;
    foreach (Project* p, Project::projects) {
        int id = p->property("id").toInt();
        if (id == 0)
            ok &= dao.insert(p, Project::TableName);
        else
            ok &= dao.update(p, Project::TableName);
        return ok && p->saveTimespans();
    }
}

bool Project::saveTimespans()
{
    bool ok = true;
    foreach (TimeSpan ts, getTimeSpans()) {
        ok &= ts.save(property("id"));
    }
    return ok;
}
