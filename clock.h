#ifndef CLOCK_H
#define CLOCK_H

#include <QObject>

class Clock : public QObject
{
    Q_OBJECT
public:
    explicit Clock(QObject *parent = 0);
    void getSecondsElapsed();
    void start();
    void stop();
    void reset();
    QString getFormatted();

protected:
    virtual void timerEvent(QTimerEvent *);

private:
    int seconds;
    int timerId;
    
signals:
    void ticked();
    
public slots:
    
};

#endif // CLOCK_H
