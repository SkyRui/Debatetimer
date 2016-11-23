#ifndef LOGINUI_H
#define LOGINUI_H

#include <QDialog>
#include <QMouseEvent>
#include <QPoint>
#include <QSound>

namespace Ui {
class LoginUi;
}

class LoginUi : public QDialog
{
    Q_OBJECT

public:
    explicit LoginUi(QWidget *parent = 0);
    ~LoginUi();

    QSound* WarningTone = nullptr;
    QSound* CountdownTone = nullptr;
    QSound* TimeoutTone = nullptr;


protected:
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent* event);

private:
    Ui::LoginUi *ui;
    QPoint windowPos;
    QPoint mousePos;
    QPoint dPos;

private slots:
    void showParentWindowSlot();
};

#endif // LOGINUI_H
