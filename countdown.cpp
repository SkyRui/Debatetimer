#include "countdown.h"
#include <QDebug>

Countdown::Countdown(QLabel *label)
{
    this->label = label;
    this->timer = new QTimer(this);
    QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(redrawLabelSlot()));
}

Countdown::~Countdown()
{
    delete timer;
    delete WarningTone;
    delete CountdownTone;
    delete TimeoutTone;
}

void Countdown::setLabel(QLabel *label)
{
    this->label = label;
}

QLabel *Countdown::getLabel()
{
    return this->label;
}

void Countdown::setTime(int time)
{
    this->time = time;
    this->label->setNum(time);
}

void Countdown::setTimeStop(int time)
{
    this->time = time;
    this->label->setNum(time);
    this->timer->stop();
}

int Countdown::getTime()
{
    return this->time;
}

void Countdown::setWarningTone(QSound *sound)
{
    this->WarningTone = sound;
}

void Countdown::setCountdownTone(QSound *sound)
{
    this->CountdownTone = sound;
}

void Countdown::setTimeoutTone(QSound *sound)
{
    this->TimeoutTone = sound;
}

void Countdown::pauseTime()
{
    timer->stop();
    if (5 >= this->time)    CountdownTone->stop();
}

void Countdown::startTime()
{
    timer->start(1000);
}

void Countdown::startTime(int time)
{
    setTime(time);
    timer->start(1000);
}

void Countdown::haveWarnningToneStartTime()         //总计时器的时间小于30秒时，开始时响起提示音
{
    timer->start(1000);
        if (31 == this->time)     WarningTone->play();
        if (5 >= this->time && 0 > this->time)    CountdownTone->play();
}

void Countdown::redrawLabelSlot()
{
    this->time --;
    this->label->setNum(this->time);
    if (31 == this->time)     WarningTone->play();
    if (5 == this->time)    CountdownTone->play();
    if (0 == this->time)      TimeoutTone->play();
}
