#include "launchbutton.h"
#include <QProcess>
#include <QMouseEvent>
#include <iostream>

LaunchButton::LaunchButton(QString name, QString path, QIcon icon, QWidget *parent)
    : m_name(name), m_path(path), QPushButton(parent)
{
    setIcon(icon);
    setIconSize(QSize(50, 50));
    setStyleSheet("background: solid;");
    setMouseTracking(true);

    QObject::connect(this, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    QObject::connect(this, SIGNAL(mouseMoved()), parent, SLOT(onMouseMoved()));
}

void LaunchButton::resize(const QSize &size)
{
    QPushButton::resize(size);
    setIconSize(size);
}

void LaunchButton::onButtonClicked()
{
    QProcess().startDetached(m_path);
}

void LaunchButton::mouseMoveEvent(QMouseEvent* /*event*/)
{
    emit mouseMoved();
}
