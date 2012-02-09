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
    Project p;    

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testDBCreation();
    void testInsert();
    void testProjectSave();
    void testRestoreProject();
    void testFindById();
    void testSelect();   
    void testDelete();
};

GenericDaoTest::GenericDaoTest()
{
}

void GenericDaoTest::initTestCase()
{
    p.setName("Projeto Secreto");
    p.setDescription("Projeto Ultra Secreto");
    QDateTime now = QDateTime::currentDateTime();
    ts = TimeSpan(QDateTime::currentDateTime(), QDateTime::currentDateTime().addSecs(3000));
    int size = 50;
    tss.reserve(size);
    for ( int i=1; i<=size; i++ ) {
        TimeSpan ts(now, now.addSecs(i*60));
        p.addTimeTrackingSession(ts);
        tss << ts;
    }
    QString path(QDir::homePath());
    path.append(QDir::separator()).append(DB_NAME);
    path = QDir::toNativeSeparators(path);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    db.open();
    QSqlQuery query("create table project(id integer primary key, name text, description text)");
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


void GenericDaoTest::testInsert()
{
    DBUtils::GenericDao dao;
    QVERIFY(dao.insertOrUpdate(&p, PROJECT_TABLE));
    QVERIFY(dao.insertOrUpdate(&ts, TIMESPAN_TABLE, "projectId", QVariant(p.property("id"))));
    foreach (TimeSpan ts, tss) {
        QVERIFY(dao.insertOrUpdate(&ts, TIMESPAN_TABLE, "projectId", QVariant(p.property("id"))));
    }
}


void GenericDaoTest::testFindById()
{
    DBUtils::GenericDao dao;
    QObject * o = dao.findById(ts.property("id").toInt(), ts.metaObject(), TIMESPAN_TABLE);
    if ( !o )
        QVERIFY(false);
    else {
        TimeSpan *ts2 = dynamic_cast<TimeSpan*>(o);
        QVERIFY(*ts2 == ts);
        delete o;
    }
}


void GenericDaoTest::testSelect()
{
    DBUtils::GenericDao dao;
    QVector<QObject*> rs = dao.select(ts.metaObject(), "", TIMESPAN_TABLE);
    QVERIFY(rs.count() > 0);
    foreach (QObject* o , rs) {
        TimeSpan *ts2 = dynamic_cast<TimeSpan*>(o);
        QVERIFY(ts2 != 0);
    }

    rs.clear();
}


void GenericDaoTest::testDelete()
{
    DBUtils::GenericDao dao;
    QVERIFY(dao.remove(&ts, TIMESPAN_TABLE));
    foreach (TimeSpan ts, tss) {
        QVERIFY(dao.remove(&ts, TIMESPAN_TABLE));
    }
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

void GenericDaoTest::testProjectSave()
{
    QVERIFY(Project::save());
    QVERIFY(Project::save());
    DBUtils::GenericDao dao;
    QVector<QObject*> timespans = dao.select(ts.metaObject(), "projectId = " + p.property("id").toString(), TimeSpan::TableName);
    QVERIFY(timespans.count() == p.getTimeSpans().count());
}


QTEST_APPLESS_MAIN(GenericDaoTest);


#include "tst_genericdaotest.moc"
