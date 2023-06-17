#ifndef PAGE_H
#define PAGE_H

#include <QFrame>

namespace Ui {
class Page;
}

class Page : public QFrame
{
    Q_OBJECT

public:
    explicit Page(QWidget *parent = nullptr);
    ~Page();

protected:
    void showEvent(QShowEvent *e) override;
    void hideEvent(QHideEvent *e) override;
    bool event(QEvent *e) override;

private:
    Ui::Page *ui;
};

#endif // PAGE_H
