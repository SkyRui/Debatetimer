#include "loginui.h"
#include "ui_loginui.h"
#include <QDebug>

LoginUi::LoginUi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginUi)
{
    ui->setupUi(this);

    this->setWindowTitle("辩论计时 1.0");
    this->setFixedSize( this->width (),this->height ());

    this->WarningTone   = new QSound(QCoreApplication ::applicationDirPath() + "/res/warning.wav", this);
    this->CountdownTone = new QSound(QCoreApplication ::applicationDirPath() + "/res/countdown.wav", this);
    this->TimeoutTone   = new QSound(QCoreApplication ::applicationDirPath() + "/res/timeout.wav", this);

    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(showParentWindowSlot()));

    QObject::connect(ui->warningButton,     SIGNAL(clicked()), this->WarningTone,   SLOT(play()));
    QObject::connect(ui->countdownButton,   SIGNAL(clicked()), this->CountdownTone, SLOT(play()));
    QObject::connect(ui->timeoutButton,     SIGNAL(clicked()), this->TimeoutTone,   SLOT(play()));
    QObject::connect(ui->timeoutButton,     SIGNAL(clicked()), this->CountdownTone, SLOT(stop()));
}

LoginUi::~LoginUi()
{
    delete WarningTone;
    delete CountdownTone;
    delete TimeoutTone;

    delete ui;

    qDebug()<<"loginui";
}

void LoginUi::mousePressEvent(QMouseEvent *event)
{
    this->windowPos = this->pos();              // 获得部件当前位置
    this->mousePos  = event->globalPos();       // 获得鼠标位置
    this->dPos      = mousePos - windowPos;     // 移动后部件所在的位置
}

void LoginUi::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() - this->dPos);
}

void LoginUi::showParentWindowSlot()
{
    parentWidget()->show();
    delete this;
}
