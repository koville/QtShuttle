#include "MySlider.h"
#include "ShuttleHelper.h"

MySlider::MySlider(QWidget *parent)
    : QSlider(parent)
    , m_adjustFlag(false)
{
}

void MySlider::ShuttleClicked()
{
    m_adjustFlag^=true;
    ShuttleHelper::Instance().SetAdjustFlag(m_adjustFlag);
}

void MySlider::ShuttleAdd()
{
    int value = this->value();
    int step = this->singleStep();
    this->setValue(value + step);
}

void MySlider::ShuttleReduce()
{
    int value = this->value();
    int step = this->singleStep();
    this->setValue(value - step);
}
