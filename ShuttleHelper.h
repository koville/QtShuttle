#ifndef SHUTTLEHELPER_H
#define SHUTTLEHELPER_H

#include <QWidget>
#include <QVector>
#include <QQueue>

typedef struct _SHUTTLE_DATA_
{
    QVector<QWidget*>                 shuttleVec;
    QVector<QWidget*>::const_iterator shuttleIter;
}ShuttleDate;

    class ShuttleHelper : public QObject
{
    Q_OBJECT
public:
    static ShuttleHelper& Instance();
    static void Construct(QObject *parent = nullptr);
    static void Destruct();

    void PopTopWindow();
    void RegeisterNewWindow(QVector<QWidget*>, QVector<QWidget*>::const_iterator);
    void RegeisterVoidTop();
    void UpdateTopWindow(QVector<QWidget*>, QVector<QWidget*>::const_iterator);
    void UpdateMainWindow(QVector<QWidget*>, QVector<QWidget*>::const_iterator);
    void UpdateTopWinIter(QWidget *);
    void SetAdjustFlag(bool flag = true);
    void SetClickFlag();

public slots:
    void onLeft();
    void onRight();
    void onEnter();

private:
    explicit ShuttleHelper(QObject *parent = nullptr);
    virtual ~ShuttleHelper();
    ShuttleHelper(ShuttleHelper& ) = delete;
    ShuttleHelper(ShuttleHelper&&) = delete;
    ShuttleHelper& operator=(const ShuttleHelper& ) = delete;
    ShuttleHelper& operator=(const ShuttleHelper&&) = delete;

private:
    static ShuttleHelper *s_instance;
    bool                  m_adjustFlag; // 调节标志  false改变光标位置 true为选中并调节
    bool                  m_clickFlag;  // 默认false 转动编码器后置为true  焦点出现
    QQueue<ShuttleDate>   m_shuttleQueue;
};

#endif // SHUTTLEHELPER_H
