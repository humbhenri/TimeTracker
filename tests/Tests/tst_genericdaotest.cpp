#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QFile>
#include "timespan.h"
#include "genericdao.h"

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
    path.append(QDir::separator()).append("time_tracker_test.db");
    path = QDir::toNativeSeparators(path);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    db.open();
    if (db.isOpen()) {
        // create table timespan
        QSqlQuery query("create table timespan(id integer primary key, start text, end text)");
    }
}

void GenericDaoTest::cleanupTestCase()
{
    QSqlDatabase db = QSqlDatabase::database();
    db.close();
    QString path(QDir::homePath());
    path.append(QDir::separator()).append("time_tracker_test.db");
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
