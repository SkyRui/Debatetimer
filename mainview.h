#ifndef MAINVIEW_H
#define MAINVIEW_H
#include <QWidget>
#include <QSound>
#include <QTimer>

#include "countdown.h"
#include "loginui.h"

namespace Ui {
class MainView;
}

class MainView : public QWidget
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();

    //初始化函数集合
    void initializeUi();
    void disconnectAllButtom();

private:
    Ui::MainView *mainUI;

    int LINK = 1;
public:
    LoginUi* loginui;

    QSound* WarningTone   = nullptr;
    QSound* CountdownTone = nullptr;
    QSound* TimeoutTone   = nullptr;

    Countdown* mainLabelTimer     = nullptr;
    Countdown* positiveLabelTimer = nullptr;
    Countdown* negativeLabelTimer = nullptr;

private slots:
    void stopAllTimerSlot();
    void upLinkSlot();
    void nextLinkSlot();

    void zhengfang20sSlot();
    void zhengfang30sSlot();
    void fanfang20sSlot();
    void fanfang30sSlot();

    void zhengfangpanwenSlot();
    void fanfangpanwenSlot();
    void shuangfanggongbianSlot();

public:
    //正方立论
    void zhengfang_lilun();
    //反方立论
    void fanfang_lilun();
    //正方盘问
    void zhengfang_panwen();
    //反方盘问
    void fanfang_panwen();
    //正方驳论
    void zhengfang_bolun();
    //反方驳论
    void fanfang_bolun();
    //双方攻辩
    void shuangfang_gongbian();
    //自由辩论
    void ziyou_bianlun();
    //反方总结
    void fanfang_zongjie();
    //正反总结
    void zhengfang_zongjie();

    void zhengfang();
    void fanfang();
};

#endif // MAINVIEW_H
