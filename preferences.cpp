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

#include "preferences.h"
#include "trayiconcommand.h"
#include "project.h"
#include <QStringList>
#include <QSettings>
#include <QDesktopServices>
#include <QDir>
#include <QApplication>

QString Preferences::SINGLE_CLICK = QString("Preferences/SingleClickCommand");
QString Preferences::DOUBLE_CLICK = QString("Preferences/DoubleClickCommand");
QString Preferences::CURRENT_PROJECT = QString("Preferences/CurrentProject");
QString Preferences::PROJECTS_XML_FILE = QString("time_tracker.xml");

Preferences::Preferences(QObject *parent) :
    QObject(parent)
{
}

Preferences::~Preferences()
{
}

QStringList Preferences::commandNames()
{
    if (commands)
        return QStringList(commands->keys());
    else
        return QStringList();
}

void Preferences::loadPreferences()
{
    QSettings settings;
    setSingleClick(settings.value(SINGLE_CLICK, QVariant(commands->keys().at(0))).toString());
    setDoubleClick(settings.value(DOUBLE_CLICK, QVariant(commands->keys().at(0))).toString());
    setCurrentProject(settings.value(CURRENT_PROJECT, QVariant(QString::null)).toString());
    emit changed();
}

void Preferences::savePreferences()
{
    QSettings settings;
    settings.setValue(SINGLE_CLICK, getSingleClickCommandName());
    settings.setValue(DOUBLE_CLICK, getDoubleClickCommandName());
    settings.setValue(CURRENT_PROJECT, getCurrentProject());
}

void Preferences::setSingleClick(const QString &command)
{
    singleClick = commands->value(command);
    emit changed();
}

void Preferences::setDoubleClick(const QString &command)
{
    doubleClick = commands->value(command);
    emit changed();
}

TrayIconCommand* Preferences::getSingleClick()
{
    return singleClick;
}

TrayIconCommand* Preferences::getDoubleClick()
{
    return doubleClick;
}

QString Preferences::getSingleClickCommandName()
{
    if (commands)
        return commands->key(singleClick);
    else
        return QString::null;
}

QString Preferences::getDoubleClickCommandName()
{
    if (commands)
        return commands->key(doubleClick);
    else
        return QString::null;
}

void Preferences::setCommands(QMap<QString,TrayIconCommand*> *map)
{
    commands = map;
    singleClick = commands->begin().value();
    doubleClick = commands->begin().value();
}

QString Preferences::getProjectsXMLFile()
{
    QDir dir(QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation) +
             QString("/") + QApplication::instance()->applicationName() + QString("/"));
    if (!dir.exists()) {
        qDebug("Dir %s doesn't exists", qPrintable(dir.path()));
        if (!dir.mkdir(dir.path()))
            qDebug("Error: cannot create dir %s", qPrintable(dir.path()));
    }

    return dir.path() + QString("/") + Preferences::PROJECTS_XML_FILE;
}

void Preferences::setCurrentProject(const QString & project) {
    emit projectChanged(Project::getProjectByName(currentProject));
    currentProject = project;
}
