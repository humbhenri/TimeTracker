#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QObject>
#include <QMap>

class TrayIconCommand;

class Preferences : public QObject
{
    Q_OBJECT
public:
    explicit Preferences(QObject *parent = 0);
    virtual ~Preferences();
    QStringList commandNames();
    void loadPreferences();
    void savePreferences();
    void setSingleClick(const QString&);
    void setDoubleClick(const QString&);
    TrayIconCommand* getSingleClick();
    TrayIconCommand* getDoubleClick();
    QString getSingleClickCommandName();
    QString getDoubleClickCommandName();
    void setCommands(QMap<QString,TrayIconCommand*> *map);
    inline void setCurrentProject(const QString & project) { currentProject = project; emit changed();}
    QString getCurrentProject() const { return currentProject; }
    static QString SINGLE_CLICK;
    static QString DOUBLE_CLICK;
    static QString CURRENT_PROJECT;
    static QString PROJECTS_XML_FILE;

private:
    QMap<QString, TrayIconCommand*> *commands;
    TrayIconCommand *singleClick;
    TrayIconCommand *doubleClick;
    QString currentProject;

signals:
    void changed();

public slots:

};

#endif // PREFERENCES_H
