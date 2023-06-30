#include <QKeyEvent>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ShuttleHelper.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_page(nullptr)
{
    ui->setupUi(this);
    m_page = new Page();
    connect(ui->btn1, &MyPushButton::clicked, m_page, &Page::show);
    connect(ui->btn2, &MyPushButton::clicked, m_page, &Page::show);
    connect(ui->btn3, &MyPushButton::clicked, m_page, &Page::show);
    connect(ui->btn4, &MyPushButton::clicked, m_page, &Page::show);
    connect(ui->btn5, &MyPushButton::clicked, m_page, &Page::show);
    connect(ui->btn6, &MyPushButton::clicked, m_page, &Page::show);
    connect(ui->btn7, &MyPushButton::clicked, m_page, &Page::show);
    connect(ui->btn8, &MyPushButton::clicked, m_page, &Page::show);

    QVector<QWidget*> vec;
    vec << ui->btn1 << ui->btn2 << ui->btn3 << ui->btn4
        << ui->btn5 << ui->btn6 << ui->btn7 << ui->btn8
        << ui->horizontalScrollBar;
    ShuttleHelper::Instance().UpdateMainWindow(vec, ui->btn1);
}

MainWindow::~MainWindow()
{
    delete ui;
    if(nullptr != m_page)
    {
        delete m_page;
    }
}

bool MainWindow::event(QEvent *e)
{
    if(QEvent::MouseButtonPress == e->type())
    {
        ShuttleHelper::Instance().SetClickFlag();
    } // 以下模拟编码器操作
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
