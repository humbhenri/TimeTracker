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
    QVector<TimeSpan> tss;

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testDBCreation();
    void testInsert();
    void testFindById();
    void testSelect();
    void testUpdate();
    void testDelete();
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
        tss << TimeSpan(now, now.addSecs(i*60));
    }
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
    tss.clear();
}

void GenericDaoTest::testDBCreation()
{
    QVERIFY(QSqlError::NoError == QSqlDatabase::database().lastError().type());
}

void GenericDaoTest::testFindById()
{
    DBUtils::GenericDao dao;
    QObject * o = dao.findById(1, ts.metaObject(), "timespan");
    if ( !o )
        QVERIFY(1 == 0);
    else {
        TimeSpan *ts2 = dynamic_cast<TimeSpan*>(o);
        QVERIFY(*ts2 == ts);
        delete o;
    }
}


void GenericDaoTest::testSelect()
{
    DBUtils::GenericDao dao;
    QVector<QObject*> rs = dao.select(ts.metaObject(), "", "timespan");
    QVERIFY(rs.count() > 0);
    qDebug() << rs.count();
    foreach (QObject* o , rs) {
        TimeSpan *ts2 = dynamic_cast<TimeSpan*>(o);
        QVERIFY(ts2 != 0);
    }

    rs.clear();
}


void GenericDaoTest::testDelete()
{
    DBUtils::GenericDao dao;
    QVERIFY(dao.remove(&ts, "timespan"));
    foreach (TimeSpan ts, tss) {
        QVERIFY(dao.remove(&ts, "timespan"));
    }
}

void GenericDaoTest::testUpdate()
{
    DBUtils::GenericDao dao;
    ts.setStart(QDateTime::currentDateTime());
    QVERIFY(dao.update(&ts, "timespan"));
}

void GenericDaoTest::testInsert()
{
    DBUtils::GenericDao dao;
    QVERIFY(dao.insert(&ts, "timespan"));
    foreach (TimeSpan ts, tss) {
        QVERIFY(dao.insert(&ts, "timespan"));
    }
}



QTEST_APPLESS_MAIN(GenericDaoTest);

#include "tst_genericdaotest.moc"
