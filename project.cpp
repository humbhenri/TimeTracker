#include "project.h"

QList<Project*> Project::projects;

Project::Project(QObject *parent) :
    QObject(parent)
{
}

void Project::addTimeTrackingSession(const TimeSpan &timeSpan)
{
    timeSpans.push_back(timeSpan);
    emit changed();

#ifndef QT_NO_DEBUG
    qDebug("Project::addTimeTrackingSession called with project.name = %s and time span = %s",
           name.toAscii().data(),
           timeSpan.toString().toAscii().data());
#endif
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
