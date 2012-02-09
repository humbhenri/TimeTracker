#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QFile>
#include "timespan.h"
#include "genericdao.h"
#include "project.h"
#include "debugutils.h"
#define DB_NAME "test.db"
#define TIMESPAN_TABLE "timespan"
#define PROJECT_TABLE "project"

class GenericDaoTest : public QObject
{
    Q_OBJECT

public:
    GenericDaoTest();

private:
    TimeSpan ts;
    QVector<TimeSpan> tss;

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testDBCreation();
    void testSaveProject();
    void testRestoreProject();
};

GenericDaoTest::GenericDaoTest()
{
}

void GenericDaoTest::initTestCase()
{
    QDateTime now = QDateTime::currentDateTime();
    ts = TimeSpan(QDateTime::currentDateTime(), QDateTime::currentDateTime().addSecs(3000));
    int size = 50;
    tss.reserve(size);
    for ( int i=1; i<=size; i++ ) {
        TimeSpan ts(now, now.addSecs(i*60));
        tss << ts;
    }
    QString path(QDir::homePath());
    path.append(QDir::separator()).append(DB_NAME);
    path = QDir::toNativeSeparators(path);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    db.open();
    QSqlQuery query("create table project(id integer primary key, name text, description text, created text, lastModified text)");
    QSqlQuery query2("create table timespan(id integer primary key, start text, end text, projectId integer, FOREIGN KEY(projectId) REFERENCES project(id))");
}

void GenericDaoTest::cleanupTestCase()
{
    QSqlDatabase db = QSqlDatabase::database();
    db.close();
    QString path(QDir::homePath());
    path.append(QDir::separator()).append(DB_NAME);
    path = QDir::toNativeSeparators(path);
    QFile::remove(path);
    tss.clear();
}

void GenericDaoTest::testDBCreation()
{
    QVERIFY(QSqlError::NoError == QSqlDatabase::database().lastError().type());
}


void GenericDaoTest::testRestoreProject()
{
//    DBUtils::GenericDao dao;
//    Project * project = dynamic_cast<Project*>(dao.findById(p.property("id").toInt(), p.metaObject(), Project::TableName));
//    QVector<QObject*> timespans = dao.select(ts.metaObject(), "projectId = " + project->property("id").toString(), TimeSpan::TableName);
//    QVERIFY(project != 0);
//    QVERIFY(timespans.count() > 0);
//    delete project;
//    timespans.clear();
    QVERIFY(Project::restore());
}

void GenericDaoTest::testSaveProject()
{
    Project::makeProject("project 1", "Project 1 Description");
    foreach (TimeSpan ts, tss) {
        Project::getProjectByName("project 1")->addTimeTrackingSession(ts);
    }

    QVERIFY(Project::save());
    QVERIFY(Project::save());
    QVERIFY(Project::save());
    QVERIFY(Project::save());
    QVERIFY(Project::save());
    DBUtils::GenericDao dao;
    Project dummy;
    QVector<QObject*> projects = dao.select(dummy.metaObject(), "", Project::TableName);
    QVERIFY2(projects.count() == Project::getProjects().count(), qPrintable(QString::number(projects.count())));
    QVector<QObject*> timespans = dao.select(ts.metaObject(),
                                             "projectId = " + Project::getProjectByName("project 1")->property("id").toString(),
                                             TimeSpan::TableName);
    QVERIFY2(timespans.count() == tss.count(), qPrintable(QString::number(timespans.count())));
    projects.clear();
    timespans.clear();
}


QTEST_APPLESS_MAIN(GenericDaoTest);


#include "tst_genericdaotest.moc"
