#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include "ShuttleBase.h"

class MyPushButton : public QPushButton, public ShuttleBase
{
public:
    MyPushButton(QWidget *parent = nullptr);
    virtual void ShuttleClicked() override;

protected:
    bool event(QEvent *) override;
};

#endif // MYPUSHBUTTON_H
