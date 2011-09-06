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
