#include "clock.h"
#define CLOCK_TICK_MILIS 1000

Clock::Clock(QObject *parent) :
    QObject(parent),
    seconds(0)
{
}

void Clock::timerEvent(QTimerEvent *)
{
    seconds++;
    emit ticked();
}

void Clock::start()
{
    timerId = startTimer(CLOCK_TICK_MILIS);
}

void Clock::stop()
{
    killTimer(timerId);
}

void Clock::reset()
{
    seconds = 0;
}

QString Clock::getFormatted()
{
    int hours = seconds/3600;
    int minutes = (seconds/60) % 60;
    int secs = seconds % 60;
    return QString::number(hours).rightJustified(2, '0') + ":" +
            QString::number(minutes).rightJustified(2, '0') + ":" +
            QString::number(secs).rightJustified(2, '0');
}
