#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include <QList>
#include <QDomDocument>
#include "timespan.h"

class Project : public QObject
{
    Q_OBJECT
public:    
    inline void setName(const QString & newName) { name = newName.trimmed(); emit changed();}
    inline QString getName() const { return name; }
    inline void setDescription(const QString & newDescription) { description = newDescription.trimmed(); emit changed();}
    inline QString getDescription() const { return description; }
    void addTimeTrackingSession(const TimeSpan &timeSpan);
    inline QList<TimeSpan> getTimeSpans() const { return timeSpans; }
    QString totalTimeSpent() const;    
    static Project* makeProject(const QString & name, const QString & description);
    static QList<Project*> getProjects();
    static Project* getProjectByName(const QString & name);
    static QDomElement getAllProjectsAsDomElement(QDomDocument &d);
    static void createProjectsFromDomElement(const QDomElement &d);

signals:
    void changed();

public slots:

private:
    Project(QObject *parent = 0);
    QString name;
    QString description;
    QList<TimeSpan> timeSpans;
    static QList<Project*> projects;
};

#endif // PROJECT_H
