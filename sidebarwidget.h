#ifndef SIDEBARWIDGET_H
#define SIDEBARWIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>
#include "launchbutton.h"

class QPushButton;
class QPropertyAnimation;

class SidebarWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit SidebarWidget(const int desktopWidth, const int desktopHeight, QWidget *parent = 0);
    ~SidebarWidget();

public slots:
    void onMouseMoved();
    void openSettingsDialog();

protected:
    void mouseMoveEvent(QMouseEvent* /*event*/);

private:
    void initTrayIcon();
    QPushButton* m_closeButton;
    QPushButton* m_optionsButton;
    QList<LaunchButton*> m_launchButtons;
    QPropertyAnimation *m_animation;
    bool m_isMoving;
    const int m_desktopWidth;
    const int m_desktopHeight;
    QTimer *m_animationTimer;

    QAction *m_optionsAction;
    QAction *m_quitAction;
    QSystemTrayIcon *m_trayIcon;
    QMenu *m_trayIconMenu;

private slots:
    void closeButtonClicked();
    void hideWidget();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
};

#endif // SIDEBARWIDGET_H
