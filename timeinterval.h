#ifndef TIMEINTERVAL_H
#define TIMEINTERVAL_H



/**
  * A TimeInterval consist of the time interval between the beginning and the end of a tracking session.
  * A project consist of many TimeIntervals.
  */
class TimeInterval
{
public:
    TimeInterval();
    QDateTime getBeginning();
    QDateTime getEnd();
private:
    QDateTime beginning;
    QDateTime end;
};

#endif // TIMEINTERVAL_H
