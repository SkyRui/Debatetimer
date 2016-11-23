#include "mainview.h"
#include "ui_mainview.h"

#include <QDebug>

MainView::MainView(QWidget *parent) : QWidget(parent), mainUI(new Ui::MainView)
{
    mainUI->setupUi(this);

    initializeUi();
}

MainView::~MainView()
{
    delete mainUI;
}

//初始化界面与对象
void MainView::initializeUi()
{   
    this->WarningTone   = new QSound(QCoreApplication ::applicationDirPath() + "/res/warning.wav", this);
    this->CountdownTone = new QSound(QCoreApplication ::applicationDirPath() + "/res/countdown.wav", this);
    this->TimeoutTone   = new QSound(QCoreApplication ::applicationDirPath() + "/res/timeout.wav", this);

    this->mainLabelTimer     = new Countdown(mainUI->mainUILabel);
    this->positiveLabelTimer = new Countdown(mainUI->positiveUILabel);
    this->negativeLabelTimer = new Countdown(mainUI->negativeUILable);

    this->mainLabelTimer->setWarningTone(this->WarningTone);
    this->mainLabelTimer->setCountdownTone(this->CountdownTone);
    this->mainLabelTimer->setTimeoutTone(this->TimeoutTone);

    this->positiveLabelTimer->setWarningTone(this->WarningTone);
    this->positiveLabelTimer->setCountdownTone(this->CountdownTone);
    this->positiveLabelTimer->setTimeoutTone(this->TimeoutTone);

    this->negativeLabelTimer->setWarningTone(this->WarningTone);
    this->negativeLabelTimer->setCountdownTone(this->CountdownTone);
    this->negativeLabelTimer->setTimeoutTone(this->TimeoutTone);

    loginui = new LoginUi(this);
    loginui->show();
    this->setFixedSize(this->width(), this->height());

    QObject::connect(mainUI->nextButton, SIGNAL(clicked()), this, SLOT(nextLinkSlot()));
    QObject::connect(mainUI->upButton,   SIGNAL(clicked()), this, SLOT(upLinkSlot()));
    QObject::connect(mainUI->stopButton, SIGNAL(clicked()), this, SLOT(stopAllTimerSlot()));
}

//清空按键connect
void MainView::disconnectAllButtom()
{
    mainUI->positiveSideButton->disconnect();
    mainUI->negativeSideButton->disconnect();

    this->mainLabelTimer->setTimeStop(0);
    this->positiveLabelTimer->setTimeStop(0);
    this->negativeLabelTimer->setTimeStop(0);
}

void MainView::stopAllTimerSlot()
{
    this->mainLabelTimer->pauseTime();
    this->positiveLabelTimer->pauseTime();
    this->negativeLabelTimer->pauseTime();
}

//比赛环节队列
void MainView::nextLinkSlot()
{
    //清理两个功能建与槽的连接
    disconnectAllButtom();

    switch (LINK++)
    {
    case 1:
        mainUI->mainLabel->setText("正方立论");
        mainUI->nextLabel->setText("反方立论");
        qDebug()<<"正方立论";
        zhengfang_lilun();

        break;

    case 2:
        mainUI->mainLabel->setText("反方立论");
        mainUI->nextLabel->setText("正方盘问");
        qDebug()<<"反方立论";
        fanfang_lilun();
        break;

    case 3:
        mainUI->mainLabel->setText("正方盘问");
        mainUI->nextLabel->setText("反方盘问");
        qDebug()<<"正方盘问";
        zhengfang_panwen();
        break;

    case 4:
        mainUI->mainLabel->setText("反方盘问");
        mainUI->nextLabel->setText("正方驳论");
        qDebug()<<"反方盘问";
        fanfang_panwen();
        break;
    case 5:
        mainUI->mainLabel->setText("正方驳论");
        mainUI->nextLabel->setText("反方驳论");
        qDebug()<<"正方驳论";
        zhengfang_bolun();
        break;
    case 6:
        mainUI->mainLabel->setText("反方驳论");
        mainUI->nextLabel->setText("双方攻辩");
        qDebug()<<"反方驳论";
        fanfang_bolun();
        break;
    case 7:
        mainUI->mainLabel->setText("双方攻辩");
        mainUI->nextLabel->setText("自由辩论");
        qDebug()<<"双方攻辩";
        shuangfang_gongbian();
        break;
    case 8:
        mainUI->mainLabel->setText("自由辩论");
        mainUI->nextLabel->setText("反方总结");
        qDebug()<<"自由辩论";
        ziyou_bianlun();
        break;
    case 9:
        mainUI->mainLabel->setText("反方总结陈词");
        mainUI->nextLabel->setText("正方陈词");
        qDebug()<<"反方总结";
        fanfang_zongjie();
        break;
    case 10:
        mainUI->mainLabel->setText("正方总结陈词");
        mainUI->nextLabel->setText("结束");
        qDebug()<<"正方总结";
        zhengfang_zongjie();
        break;
    default :
        mainUI->mainLabel->setText("比赛结束");
        //结束界面

        (this->LINK) --;
    }
}

//进入前一回合
void MainView::upLinkSlot()
{
    if (3 > this->LINK) return ;
    (this->LINK) -=2;
    nextLinkSlot();
    qDebug()<<"前进";
}

//短定时槽
void MainView::zhengfang20sSlot()
{
    this->positiveLabelTimer->startTime(20);
}

void MainView::zhengfang30sSlot()
{
    this->positiveLabelTimer->startTime(30);
}

void MainView::fanfang20sSlot()
{
    this->negativeLabelTimer->startTime(20);
}

void MainView::fanfang30sSlot()
{
    this->negativeLabelTimer->startTime(30);
}

void MainView::zhengfangpanwenSlot()
{
    QObject::disconnect(mainUI->positiveSideButton, SIGNAL(clicked()), this->mainLabelTimer, SLOT(startTime()));
    QObject::disconnect(mainUI->positiveSideButton, SIGNAL(clicked()), this, SLOT(zhengfangpanwenSlot()));

    QObject::connect(mainUI->positiveSideButton, SIGNAL(clicked()), this,                     SLOT(zhengfang20sSlot()));
    QObject::connect(mainUI->positiveSideButton, SIGNAL(clicked()), this->negativeLabelTimer, SLOT(pauseTime()));
    QObject::connect(mainUI->negativeSideButton, SIGNAL(clicked()), this,                     SLOT(fanfang30sSlot()));
    QObject::connect(mainUI->negativeSideButton, SIGNAL(clicked()), this->positiveLabelTimer, SLOT(pauseTime()));
}

void MainView::fanfangpanwenSlot()
{
    QObject::disconnect(mainUI->negativeSideButton, SIGNAL(clicked()), this->mainLabelTimer, SLOT(startTime()));
    QObject::disconnect(mainUI->negativeSideButton, SIGNAL(clicked()), this, SLOT(fanfangpanwenSlot()));

    QObject::connect(mainUI->negativeSideButton, SIGNAL(clicked()), this,                     SLOT(fanfang20sSlot()));
    QObject::connect(mainUI->negativeSideButton, SIGNAL(clicked()), this->positiveLabelTimer, SLOT(pauseTime()));
    QObject::connect(mainUI->positiveSideButton, SIGNAL(clicked()), this,                     SLOT(zhengfang30sSlot()));
    QObject::connect(mainUI->positiveSideButton, SIGNAL(clicked()), this->negativeLabelTimer, SLOT(pauseTime()));
}

void MainView::shuangfanggongbianSlot()
{
    QObject::disconnect(mainUI->negativeSideButton, SIGNAL(clicked()), this->mainLabelTimer,     SLOT(startTime()));
    QObject::disconnect(mainUI->negativeSideButton, SIGNAL(clicked()), this,     SLOT(shuangfanggongbianSlot()));
}

//正方立论
void MainView::zhengfang_lilun()
{
    this->mainLabelTimer->setTime(180);
    this->positiveLabelTimer->setTime(180);
    zhengfang();
}

//反方立论
void MainView::fanfang_lilun()
{
    this->mainLabelTimer->setTime(180);
    this->negativeLabelTimer->setTime(180);
    fanfang();
}

//正方盘问
void MainView::zhengfang_panwen()
{
    this->mainLabelTimer->setTime(180);
    this->positiveLabelTimer->setTime(20);
    QObject::connect(mainUI->positiveSideButton, SIGNAL(clicked()), this->mainLabelTimer, SLOT(startTime()));
    QObject::connect(mainUI->positiveSideButton, SIGNAL(clicked()), this,                 SLOT(zhengfang20sSlot()));
    QObject::connect(mainUI->positiveSideButton, SIGNAL(clicked()), this, SLOT(zhengfangpanwenSlot()));

}

//反方盘问
void MainView::fanfang_panwen()
{
    this->mainLabelTimer->setTime(180);
    this->negativeLabelTimer->setTime(20);
    QObject::connect(mainUI->negativeSideButton, SIGNAL(clicked()), this->mainLabelTimer, SLOT(startTime()));
    QObject::connect(mainUI->negativeSideButton, SIGNAL(clicked()), this,                 SLOT(fanfang20sSlot()));
    QObject::connect(mainUI->negativeSideButton, SIGNAL(clicked()), this, SLOT(fanfangpanwenSlot()));
}

//正方驳论
void MainView::zhengfang_bolun()
{
    this->mainLabelTimer->setTime(90);
    this->positiveLabelTimer->setTime(90);
    zhengfang();
}

//反方驳论
void MainView::fanfang_bolun()
{
    this->mainLabelTimer->setTime(90);
    this->negativeLabelTimer->setTime(90);
    fanfang();
}

//双方攻辨
void MainView::shuangfang_gongbian()
{
    this->mainLabelTimer->setTime(180);
    this->negativeLabelTimer->setTime(20);
    QObject::connect(mainUI->negativeSideButton, SIGNAL(clicked()), this->mainLabelTimer,     SLOT(startTime()));
    QObject::connect(mainUI->negativeSideButton, SIGNAL(clicked()), this,     SLOT(shuangfanggongbianSlot()));

    QObject::connect(mainUI->positiveSideButton, SIGNAL(clicked()), this,                     SLOT(zhengfang20sSlot()));
    QObject::connect(mainUI->positiveSideButton, SIGNAL(clicked()), this->negativeLabelTimer, SLOT(pauseTime()));
    QObject::connect(mainUI->negativeSideButton, SIGNAL(clicked()), this,                     SLOT(fanfang20sSlot()));
    QObject::connect(mainUI->negativeSideButton, SIGNAL(clicked()), this->positiveLabelTimer, SLOT(pauseTime()));
}

//自由辩论
void MainView::ziyou_bianlun()
{
    this->positiveLabelTimer->setTime(240);
    this->negativeLabelTimer->setTime(240);
    QObject::connect(mainUI->positiveSideButton, SIGNAL(clicked()), this->positiveLabelTimer, SLOT(haveWarnningToneStartTime()));
    QObject::connect(mainUI->positiveSideButton, SIGNAL(clicked()), this->negativeLabelTimer, SLOT(pauseTime()));

    QObject::connect(mainUI->negativeSideButton, SIGNAL(clicked()), this->negativeLabelTimer, SLOT(haveWarnningToneStartTime()));
    QObject::connect(mainUI->negativeSideButton, SIGNAL(clicked()), this->positiveLabelTimer, SLOT(pauseTime()));
}

//反方总结
void MainView::fanfang_zongjie()
{
    this->negativeLabelTimer->setTime(240);
    this->mainLabelTimer->setTime(240);
    fanfang();
}

//正方总结
void MainView::zhengfang_zongjie()
{
    this->positiveLabelTimer->setTime(240);
    this->mainLabelTimer->setTime(240);
    zhengfang();
}

void MainView::zhengfang()
{
    QObject::connect(mainUI->negativeSideButton, SIGNAL(clicked()), this->positiveLabelTimer, SLOT(pauseTime()));
    QObject::connect(mainUI->negativeSideButton, SIGNAL(clicked()), this->mainLabelTimer,     SLOT(pauseTime()));
    QObject::connect(mainUI->positiveSideButton, SIGNAL(clicked()), this->positiveLabelTimer, SLOT(startTime()));
    QObject::connect(mainUI->positiveSideButton, SIGNAL(clicked()), this->mainLabelTimer,     SLOT(startTime()));
}

void MainView::fanfang()
{
    QObject::connect(mainUI->positiveSideButton, SIGNAL(clicked()), this->negativeLabelTimer, SLOT(pauseTime()));
    QObject::connect(mainUI->positiveSideButton, SIGNAL(clicked()), this->mainLabelTimer,     SLOT(pauseTime()));
    QObject::connect(mainUI->negativeSideButton, SIGNAL(clicked()), this->negativeLabelTimer, SLOT(startTime()));
    QObject::connect(mainUI->negativeSideButton, SIGNAL(clicked()), this->mainLabelTimer,     SLOT(startTime()));
}
