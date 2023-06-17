#include "MainWindow.h"

#include <QApplication>
#include "ShuttleHelper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShuttleHelper::Construct(nullptr);
    MainWindow w;
    w.show();

    return a.exec();
}
