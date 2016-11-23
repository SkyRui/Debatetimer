#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <QLabel>
#include <QTimer>
#include <QSound>

class Countdown : public QWidget
{
    Q_OBJECT

public:
    explicit Countdown(QLabel *label);

    ~Countdown();

public:
    QLabel* getLabel();
    void    setLabel(QLabel *label);
    void    setTime(int time);
    void    setTimeStop(int time);
    int     getTime();

    void setWarningTone(QSound* sound);
    void setCountdownTone(QSound* sound);
    void setTimeoutTone(QSound* sound);

private:
    int time = 0;
    QTimer* timer = nullptr;
    QLabel* label = nullptr;

    QSound* WarningTone =   nullptr;
    QSound* CountdownTone = nullptr;
    QSound* TimeoutTone =   nullptr;

public slots:
    void pauseTime();
    void startTime();
    void startTime(int time);  
    void haveWarnningToneStartTime();

private slots:
    void redrawLabelSlot();
};

#endif // COUNTDOWN_H
