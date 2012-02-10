#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QFile>
#include <QDate>
#include <QTime>
#include "timespan.h"
#include "genericdao.h"
#include "project.h"
#include "debugutils.h"
#define DB_NAME "test.db"
#define TIMESPAN_TABLE "timespan"
#define PROJECT_TABLE "project"
#define DEBUG_DB qPrintable(QSqlDatabase::database().lastError().text())

class GenericDaoTest : public QObject
{
    Q_OBJECT

public:
    GenericDaoTest();

private:
    QVector<TimeSpan> tss;

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testDBCreation();
    void testSave();
    void testSaveProject();
    void testRestoreProject();
};

GenericDaoTest::GenericDaoTest()
{
}

void GenericDaoTest::initTestCase()
{
    QDateTime now = QDateTime::currentDateTime();
    int size = 1;
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
//    QFile::remove(path);
    tss.clear();
}

void GenericDaoTest::testDBCreation()
{
    QVERIFY(QSqlError::NoError == QSqlDatabase::database().lastError().type());
}


void GenericDaoTest::testRestoreProject()
{
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
    DBUtils::GenericDao dao;
    Project dummy;
    TimeSpan ts;
    QVector<QObject*> projects = dao.select(dummy.metaObject(), "", Project::TableName);
    QVERIFY2(projects.count() == Project::getProjects().count(), qPrintable(QString::number(projects.count())));
    QVector<QObject*> timespans = dao.select(ts.metaObject(),
                                             "projectId = " + Project::getProjectByName("project 1")->property("id").toString(),
                                             TimeSpan::TableName);
    QVERIFY2(timespans.count() == tss.count(), qPrintable(QString::number(timespans.count())));
    projects.clear();
    timespans.clear();
}


void GenericDaoTest::testSave()
{
    DBUtils::GenericDao dao;
    TimeSpan ts(QDateTime(QDate(2000, 1, 1), QTime(12,0,0)), QDateTime(QDate(2012,12,21), QTime(12,0,0)));
    QVERIFY2(ts.save(QVariant()), DEBUG_DB);
    QVERIFY2(ts.property("id").toInt() > 0, ts.property("id").toByteArray().data());
    QVERIFY2(ts.save(QVariant()), DEBUG_DB);
    QVERIFY2(ts.save(QVariant()), DEBUG_DB);
    QVERIFY2(ts.save(QVariant()), DEBUG_DB);
    QVERIFY2(ts.save(QVariant()), DEBUG_DB);
    QVector<QObject*> timespans = dao.select(ts.metaObject(), "start = \"" + QVariant(ts.getStart()).toString() + "\"",
                                             TimeSpan::TableName);
    QVERIFY2(QSqlDatabase::database().lastError().type() == QSqlError::NoError, DEBUG_DB);
    QVERIFY2(timespans.count() == 1, qPrintable(QString::number(timespans.count())));
}

QTEST_APPLESS_MAIN(GenericDaoTest);


#include "tst_genericdaotest.moc"
