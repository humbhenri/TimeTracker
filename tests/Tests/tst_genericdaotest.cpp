#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QFile>
#include "timespan.h"
#include "genericdao.h"
#define DB_NAME "test.db"

class GenericDaoTest : public QObject
{
    Q_OBJECT

public:
    GenericDaoTest();

private:
    TimeSpan ts;

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testDBCreation();
    void testInsert();
    void testFindById();
    void testUpdate();
    void testDelete();
};

GenericDaoTest::GenericDaoTest()
{
}

void GenericDaoTest::initTestCase()
{
    ts = TimeSpan(QDateTime::currentDateTime(), QDateTime::currentDateTime().addSecs(3000));
    QString path(QDir::homePath());
    path.append(QDir::separator()).append(DB_NAME);
    path = QDir::toNativeSeparators(path);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    db.open();
    QSqlQuery query("create table timespan(id integer primary key, start text, end text)");
}

void GenericDaoTest::cleanupTestCase()
{
    QSqlDatabase db = QSqlDatabase::database();
    db.close();
    QString path(QDir::homePath());
    path.append(QDir::separator()).append(DB_NAME);
    path = QDir::toNativeSeparators(path);
    QFile::remove(path);
}

void GenericDaoTest::testDBCreation()
{
    QVERIFY(QSqlError::NoError == QSqlDatabase::database().lastError().type());
}

void GenericDaoTest::testInsert()
{
    DBUtils::GenericDao dao;
    QVERIFY(dao.insert(&ts, "timespan"));    
}


void GenericDaoTest::testFindById()
{
    DBUtils::GenericDao dao;
    QObject * o = dao.findById(1, "timespan");
    TimeSpan * timeSpan = dynamic_cast<TimeSpan*>(o);
    QVERIFY(*timeSpan == ts);
}


void GenericDaoTest::testDelete()
{
    DBUtils::GenericDao dao;
    QVERIFY(dao.remove(&ts, "timespan"));
}

void GenericDaoTest::testUpdate()
{
    DBUtils::GenericDao dao;
    ts.setStart(QDateTime::currentDateTime());
    QVERIFY(dao.update(&ts, "timespan"));
}

QTEST_APPLESS_MAIN(GenericDaoTest);

#include "tst_genericdaotest.moc"
