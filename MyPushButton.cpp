#include <QEvent>
#include "MyPushButton.h"
#include "ShuttleHelper.h"

MyPushButton::MyPushButton(QWidget *parent)
    : QPushButton(parent)
{
    this->setStyleSheet(".MyPushButton:focus { border: 2px sold #000000; }");
}

void MyPushButton::ShuttleClicked()
{
    emit clicked();
}

bool MyPushButton::event(QEvent *e)
{
    if(QEvent::MouseButtonPress == e->type())
    {
        ShuttleHelper::Instance().SetClickFlag();
        ShuttleHelper::Instance().UpdateTopWinIter(this);
    }
    else
    {}

    return QPushButton::event(e);
}
