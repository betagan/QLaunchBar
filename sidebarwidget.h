#ifndef SIDEBARWIDGET_H
#define SIDEBARWIDGET_H

#include <QWidget>
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
    QPushButton* m_closeButton;
    QPushButton* m_optionsButton;
    QList<LaunchButton*> m_launchButtons;
    QPropertyAnimation *m_animation;
    bool m_isMoving;
    const int m_desktopWidth;
    const int m_desktopHeight;
    QTimer *m_animationTimer;

private slots:
    void closeButtonClicked();
    void hideWidget();
};

#endif // SIDEBARWIDGET_H
