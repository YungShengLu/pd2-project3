#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H

#include "QHeaderfile.h"

class DigitalClock : public QLCDNumber {
    Q_OBJECT

public:
    DigitalClock(QWidget *parent = 0);

    QTimer *timer;
    QTime *time;
    QString text;

private:
    int minute, second;

public slots:
    QString showTime();

};

#endif // DIGITALCLOCK_H

