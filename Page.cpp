#include "Page.h"
#include "ui_Page.h"
#include "ShuttleHelper.h"
#include <QKeyEvent>

Page::Page(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Page)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground, true);
    hide();
    connect(ui->btn1, &MyPushButton::clicked, this, &Page::hide);
    connect(ui->btn2, &MyPushButton::clicked, this, &Page::hide);
}

Page::~Page()
{
    delete ui;
}

void Page::showEvent(QShowEvent *e)
{
    QVector<QWidget*> vec;
    vec << ui->btn2 << ui->btn1;
    ShuttleHelper::Instance().RegeisterNewWindow(vec, ui->btn2);
    QWidget::showEvent(e);
}

void Page::hideEvent(QHideEvent *e)
{
    ShuttleHelper::Instance().PopTopWindow();
    QWidget::hideEvent(e);
}

bool Page::event(QEvent *e)
{
    if(QEvent::MouseButtonPress == e->type())
    {
        ShuttleHelper::Instance().SetClickFlag();
    } // 以下模拟编码器
    else if(QEvent::KeyPress == e->type() && Qt::Key_A == dynamic_cast<QKeyEvent*>(e)->key())
    {
        ShuttleHelper::Instance().onLeft();
    }
    else if(QEvent::KeyPress == e->type() && Qt::Key_D == dynamic_cast<QKeyEvent*>(e)->key())
    {
        ShuttleHelper::Instance().onRight();
    }
    else if(QEvent::KeyPress == e->type() &&
             (Qt::Key_Enter == dynamic_cast<QKeyEvent*>(e)->key() || Qt::Key_Return == dynamic_cast<QKeyEvent*>(e)->key()))
    {
        ShuttleHelper::Instance().onEnter();
    }
    else
    {}

    return QWidget::event(e);
}

