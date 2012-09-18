#include <QtGui/QApplication>
#include <QDesktopWidget>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QMainWindow>
#include "sidebarwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("betaworx");
    QCoreApplication::setOrganizationDomain("betaworx.de");
    QCoreApplication::setApplicationName("QLaunchBar");

    if (!QSystemTrayIcon::isSystemTrayAvailable())
    {
        QMessageBox::critical(0, QObject::tr("Sorry, systray required"),
                                 QObject::tr("We have been unable to detect a systray"
                                             " on this system. QLaunchBar cannot run without"
                                             " one and will now exit."));
        return 1;
    }

    QApplication::setQuitOnLastWindowClosed(false);

    const int desktopWidth = QApplication::desktop()->width();
    const int desktopHeight = QApplication::desktop()->height();
    //QMainWindow window;
    //window.setVisible(true);
    //window.show();
    SidebarWidget w(desktopWidth, desktopHeight);
    w.show();
    //w.setVisible(true);
    return a.exec();
}
