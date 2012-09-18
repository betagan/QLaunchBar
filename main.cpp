#include <QtGui/QApplication>
#include <QDesktopWidget>
#include "sidebarwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    const int desktopWidth = QApplication::desktop()->width();
    const int desktopHeight = QApplication::desktop()->height();
    SidebarWidget w(desktopWidth, desktopHeight);
    w.show();
    
    return a.exec();
}
