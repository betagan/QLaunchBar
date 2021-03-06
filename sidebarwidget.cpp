#include "sidebarwidget.h"
#include <QPushButton>
#include <QFileIconProvider>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QTimer>
#include <QAction>
#include <QMenu>
#include <QApplication>


#include "Settings/settingswidget.h"

SidebarWidget::SidebarWidget(const int desktopWidth, const int desktopHeight, QWidget *parent) :
    QWidget(parent), m_desktopWidth(desktopWidth), m_desktopHeight(desktopHeight)
{
    // Define Window Position (Right side of Screen, hidden by default)
    setContentsMargins(0,0,0,0);
    resize(QSize(70,300));
    setGeometry(desktopWidth - 2, desktopHeight/2 - 200, 70, 300);

    // no Window Border and Close/Minimize-SystemButtons and AlwaysOnTop
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(windowFlags() | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);

    // Button: Close Widget
    m_closeButton = new QPushButton(QIcon(":/DefaultIcons/closeButtonIcon"), "", NULL);
    m_closeButton->setIconSize(QSize(25,25));
    m_closeButton->setStyleSheet("background:solid;");
    QObject::connect(m_closeButton, SIGNAL(clicked()), this, SLOT(closeButtonClicked()));

    // Button: Options Dialog
    m_optionsButton = new QPushButton(QIcon(":/DefaultIcons/optionsButtonIcon"), "", NULL);
    m_optionsButton->setIconSize(QSize(25,25));
    m_optionsButton->setStyleSheet("background:solid;");
    QObject::connect(m_optionsButton,SIGNAL(clicked()),this,SLOT(openSettingsDialog()));

    // example app button, to be removed on settingsdialog completed FIXME
    QString exampleAppPath("C:\\Users\\betagan\\Downloads\\putty.exe");
    QIcon exampleIcon(QFileIconProvider().icon(QFileInfo(exampleAppPath)));
    LaunchButton *putty = new LaunchButton("PuTTY", exampleAppPath, exampleIcon, this);
    m_launchButtons.push_back(putty);
    LaunchButton *putty2 = new LaunchButton("PuTTY", exampleAppPath, exampleIcon, this);
    m_launchButtons.push_back(putty2);
    LaunchButton *putty3 = new LaunchButton("PuTTY", exampleAppPath, exampleIcon, this);
    m_launchButtons.push_back(putty3);
    LaunchButton *putty4 = new LaunchButton("PuTTY", exampleAppPath, exampleIcon, this);
    m_launchButtons.push_back(putty4);
    LaunchButton *putty5 = new LaunchButton("PuTTY", exampleAppPath, exampleIcon, this);
    m_launchButtons.push_back(putty5);

    // Layout: Adding Buttons
    QVBoxLayout *basicLayout = new QVBoxLayout(NULL);
    QHBoxLayout *systemButtonLayout = new QHBoxLayout(NULL);
    systemButtonLayout->addWidget(m_optionsButton);
    systemButtonLayout->addWidget(m_closeButton);
    basicLayout->addLayout(systemButtonLayout);
    basicLayout->addWidget(putty);
    basicLayout->addWidget(putty2);
    basicLayout->addWidget(putty3);
    basicLayout->addWidget(putty4);
    basicLayout->addWidget(putty5);

    // Layout: Remove Spacings
    basicLayout->setSpacing(0);
    basicLayout->setMargin(0);
    basicLayout->setContentsMargins(0,0,0,0);

    // Layout: Apply to Widget
    setLayout(basicLayout);

    initTrayIcon();

    QObject::connect(m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    m_trayIcon->setIcon(QIcon(":/DefaultIcons/trayIcon"));
    m_trayIcon->setToolTip(tr("QLaunchBar"));
    m_trayIcon->show();

    // initialize Animation system for sliding widget on mouseover
    m_animation = new QPropertyAnimation(this, "geometry");
    m_isMoving = false;
    m_animationTimer = new QTimer(this);
    QObject::connect(m_animationTimer, SIGNAL(timeout()),this,SLOT(hideWidget()));
}

SidebarWidget::~SidebarWidget()
{
    delete m_closeButton;

    while (!m_launchButtons.empty())
        delete m_launchButtons.takeLast();

    delete m_animation;
    delete m_animationTimer;
}

void SidebarWidget::hideWidget()
{
    m_animation->stop();
    m_animation->setDuration(250);
    m_animation->setStartValue(geometry());
    m_animation->setEndValue(QRect(m_desktopWidth - 2, m_desktopHeight/2 - 200, 70, 300));
    m_animation->start();
    m_isMoving = false;
}

void SidebarWidget::onMouseMoved()
{
    if(!m_isMoving)
    {
        m_isMoving = true;
        m_animation->stop();
        m_animation->setDuration(500);
        m_animation->setStartValue(geometry());
        m_animation->setEndValue(QRect(m_desktopWidth - 75, m_desktopHeight/2 - 200, 70, 300));
        m_animation->start();
    }

    m_animationTimer->stop();
    m_animationTimer->start(1000);
}

void SidebarWidget::mouseMoveEvent(QMouseEvent* /*event*/)
{
    onMouseMoved();
}

void SidebarWidget::closeButtonClicked()
{
    QApplication::quit();
}

void SidebarWidget::openSettingsDialog()
{
    SettingsWidget settingsWidget;
    settingsWidget.exec();
}


void SidebarWidget::initTrayIcon()
{
    m_optionsAction = new QAction(tr("&Options"), this);
    m_optionsAction->setIcon(QIcon(":/DefaultIcons/optionsButtonIcon"));
    connect(m_optionsAction, SIGNAL(triggered()), this, SLOT(openSettingsDialog()));

    m_quitAction = new QAction(tr("&Quit"), this);
    m_quitAction->setIcon(QIcon(":/DefaultIcons/closeButtonIcon"));
    connect(m_quitAction, SIGNAL(triggered()), this, SLOT(closeButtonClicked()));

    m_trayIconMenu = new QMenu(this);
    m_trayIconMenu->setTitle("QLaunchBar");
    m_trayIconMenu->addAction(m_optionsAction);
    m_trayIconMenu->addSeparator();
    m_trayIconMenu->addAction(m_quitAction);

    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setContextMenu(m_trayIconMenu);
}

void SidebarWidget::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        onMouseMoved();
        m_animationTimer->start(2000);
        break;
    case QSystemTrayIcon::MiddleClick:

        break;
    default:
        ;
    }
}
