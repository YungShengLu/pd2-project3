#include "DigitalClock.h"

DigitalClock::DigitalClock(QWidget *parent) : QLCDNumber(parent) {
    setSegmentStyle(Filled);
    setDigitCount(8);

    minute = 1;
    second = 30;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);

    showTime();

    this->setStyleSheet("QWidget { border: 0px; }");
}

QString DigitalClock::showTime() {
    time = new QTime(minute, second);
    time->setHMS(0, time->addSecs(-1).minute(), time->addSecs(-1).second());
    text = time->toString("mm:ss");

    if ((time->second() % 2) == 0) {
        text[2] = ' ';
        text[5] = ' ';
    }

    return text;
}
