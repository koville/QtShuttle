#include "ShuttleHelper.h"
#include "ShuttleBase.h"
#include <QDebug>

#define ToShuttle(x) dynamic_cast<ShuttleBase*>(x)

ShuttleHelper *ShuttleHelper::s_instance = nullptr;

ShuttleHelper& ShuttleHelper::Instance()
{
    if(nullptr == s_instance)
    {
        s_instance = new ShuttleHelper(nullptr);
    }
    return *s_instance;
}

void ShuttleHelper::Construct(QObject *parent)
{
    if(nullptr == s_instance)
    {
        s_instance = new ShuttleHelper(parent);
    }
}

void ShuttleHelper::Destruct()
{
    if(nullptr != s_instance)
    {
        delete s_instance;
        s_instance = nullptr;
    }
}

ShuttleHelper::ShuttleHelper(QObject *parent)
    : QObject(parent)
    , m_adjustFlag(false)
    , m_clickFlag(false) // 默认不显示焦点
{
    m_shuttleQueue.push_back(ShuttleDate());
}

ShuttleHelper::~ShuttleHelper()
{
}

void ShuttleHelper::onLeft() // <-
{
    QVector<QWidget*> &vec = m_shuttleQueue.last().shuttleVec;
    QVector<QWidget*>::const_iterator &iter = m_shuttleQueue.last().shuttleIter;

    if(!m_clickFlag)
    {
        m_clickFlag = true;
        (*iter)->setFocus();
    }
    else if(m_adjustFlag) // 调节
    {
        ToShuttle(*iter)->ShuttleReduce();
    }
    else // 光标移动
    {
        if(vec.constBegin() == iter)
        {
            iter = vec.constEnd()-1;
        }
        else
        {
            iter--;
        }
        (*iter)->setFocus();
    }
}

void ShuttleHelper::onRight() // ->
{
    QVector<QWidget*> &vec = m_shuttleQueue.last().shuttleVec;
    QVector<QWidget*>::const_iterator &iter = m_shuttleQueue.last().shuttleIter;

    if(!m_clickFlag)
    {
        m_clickFlag = true;
        (*iter)->setFocus();
    }
    else if(m_adjustFlag) // 调节
    {
        ToShuttle(*iter)->ShuttleAdd();
    }
    else // 光标移动
    {
        if(vec.constEnd() - 1 == iter)
        {
            iter = vec.constBegin();
        }
        else
        {
            iter++;
        }
        (*iter)->setFocus();
    }
}

void ShuttleHelper::onEnter()
{
    QVector<QWidget*>::const_iterator &iter = m_shuttleQueue.last().shuttleIter;
    if(!m_clickFlag)
    {
        m_clickFlag = true;
        (*iter)->setFocus();
    }
    else
    {
        ToShuttle(*iter)->ShuttleClicked();
    }
}

void ShuttleHelper::PopTopWindow()
{
    m_shuttleQueue.pop_back();
    SetAdjustFlag(false);
    (*m_shuttleQueue.last().shuttleIter)->setFocus();
    if(!m_clickFlag)
    {
        (*m_shuttleQueue.last().shuttleIter)->clearFocus();
    }
}

void ShuttleHelper::RegeisterNewWindow(QVector<QWidget*> vec, QWidget* widget)
{
    QVector<QWidget*>::const_iterator iter = vec.constBegin();
    if(-1 != vec.indexOf(widget))
    {
        iter = vec.constBegin() + vec.indexOf(widget);
    }
    m_shuttleQueue.push_back(ShuttleDate{ vec, iter });
    (*iter)->setFocus();
    if(!m_clickFlag)
    {
        (*iter)->clearFocus();
    }
}

void ShuttleHelper::RegeisterVoidTop() // 某些特殊情况 先创建出一个top的数据结构 使用前用Update去填充
{
    QVector<QWidget*> vec;
    QVector<QWidget*>::const_iterator iter = vec.constBegin();
    m_shuttleQueue.push_back(ShuttleDate{ vec, iter });
}

void ShuttleHelper::UpdateTopWindow(QVector<QWidget*> vec, QWidget* widget)
{
    QVector<QWidget*>::const_iterator iter = vec.constBegin();
    if(-1 != vec.indexOf(widget))
    {
        iter = vec.constBegin() + vec.indexOf(widget);
    }
    m_shuttleQueue.last().shuttleVec = vec;
    m_shuttleQueue.last().shuttleIter = iter;
    (*iter)->setFocus();
    if(!m_clickFlag)
    {
        (*iter)->clearFocus();
    }
}

void ShuttleHelper::UpdateMainWindow(QVector<QWidget*> vec, QWidget* widget)
{
    QVector<QWidget*>::const_iterator iter = vec.constBegin();
    if(-1 != vec.indexOf(widget))
    {
        iter = vec.constBegin() + vec.indexOf(widget);
    }
    m_shuttleQueue.first().shuttleVec = vec;
    m_shuttleQueue.first().shuttleIter = iter;
    (*iter)->setFocus();
    if(!m_clickFlag)
    {
        (*iter)->clearFocus();
    }
}

void ShuttleHelper::UpdateTopWinIter(QWidget *ptr)
{
    QQueue<ShuttleDate>::iterator iter = m_shuttleQueue.end()-1;
    int index = iter->shuttleVec.indexOf(ptr);
    if(-1 != index)
    {
        iter->shuttleIter = iter->shuttleVec.constBegin() + index;
    }
    if(m_shuttleQueue.begin() == iter)
    {
        m_clickFlag = false;
    }
    (*iter->shuttleIter)->setFocus();
    (*iter->shuttleIter)->clearFocus();
}

void ShuttleHelper::SetAdjustFlag(bool flag)
{
    m_adjustFlag = flag;
}

void ShuttleHelper::SetClickFlag()
{
    m_clickFlag = false;
    (*m_shuttleQueue.last().shuttleIter)->setFocus();
    (*m_shuttleQueue.last().shuttleIter)->clearFocus();
}
