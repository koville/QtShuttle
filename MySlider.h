#ifndef MYSLIDER_H
#define MYSLIDER_H

#include <QSlider>
#include "ShuttleBase.h"

class MySlider : public QSlider, public ShuttleBase
{
public:
    MySlider(QWidget *parent = nullptr);
    virtual void ShuttleClicked() override;
    virtual void ShuttleAdd() override;
    virtual void ShuttleReduce() override;

private:
    bool m_adjustFlag;
};

#endif // MYSLIDER_H
