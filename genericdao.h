#ifndef GENERICDAO_H
#define GENERICDAO_H

#include <QObject>

namespace DBUtils {

class GenericDao : public QObject
{
    Q_OBJECT
public:
    explicit GenericDao(QObject *parent = 0);
    bool insert(QObject *dto, QString tableName);
    bool remove(QObject *dto, QString tableName);
    bool update(QObject *dto, QString tableName);

signals:

public slots:

};

}

#endif // GENERICDAO_H
