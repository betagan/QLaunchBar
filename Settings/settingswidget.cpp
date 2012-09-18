#include "settingswidget.h"
#include "generalsettingswidget.h"
#include "launchentrysettingswidget.h"
#include "updatesettingswidget.h"
#include <QtGui>

SettingsWidget::SettingsWidget()
 {
     m_contentsWidget = new QListWidget;
     m_contentsWidget->setViewMode(QListView::IconMode);
     m_contentsWidget->setIconSize(QSize(96, 84));
     m_contentsWidget->setMovement(QListView::Static);
     m_contentsWidget->setMaximumWidth(128);
     m_contentsWidget->setSpacing(12);

     m_pagesWidget = new QStackedWidget;
     m_pagesWidget->addWidget(new GeneralSettingsWidget);
     m_pagesWidget->addWidget(new LaunchEntrySettingsWidget);
     m_pagesWidget->addWidget(new UpdateSettingsWidget);

     QPushButton *closeButton = new QPushButton(tr("Close"));

     createIcons();
     m_contentsWidget->setCurrentRow(0);

     QObject::connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

     QHBoxLayout *horizontalLayout = new QHBoxLayout;
     horizontalLayout->addWidget(m_contentsWidget);
     horizontalLayout->addWidget(m_pagesWidget, 1);

     QHBoxLayout *buttonsLayout = new QHBoxLayout;
     buttonsLayout->addStretch(1);
     buttonsLayout->addWidget(closeButton);

     QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->addLayout(horizontalLayout);
     mainLayout->addStretch(1);
     mainLayout->addSpacing(12);
     mainLayout->addLayout(buttonsLayout);
     setLayout(mainLayout);

     setWindowTitle(tr("Configure QLaunchBar"));
 }

 void SettingsWidget::createIcons()
 {
     QListWidgetItem *generalConfigButton = new QListWidgetItem(m_contentsWidget);
     generalConfigButton->setIcon(QIcon(":/DefaultIcons/generalSettingsIcon"));
     generalConfigButton->setText(tr("Configuration"));
     generalConfigButton->setTextAlignment(Qt::AlignHCenter);
     generalConfigButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

     QListWidgetItem *launchEntryConfigButton = new QListWidgetItem(m_contentsWidget);
     launchEntryConfigButton->setIcon(QIcon(":/DefaultIcons/launchEntrySettingsIcon"));
     launchEntryConfigButton->setText(tr("Launcher Items"));
     launchEntryConfigButton->setTextAlignment(Qt::AlignHCenter);
     launchEntryConfigButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

     QListWidgetItem *updateButton = new QListWidgetItem(m_contentsWidget);
     updateButton->setIcon(QIcon(":/DefaultIcons/updateSettingsIcon"));
     updateButton->setText(tr("Update"));
     updateButton->setTextAlignment(Qt::AlignHCenter);
     updateButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

     QObject::connect(m_contentsWidget,  SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
                      this,              SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
 }

 void SettingsWidget::changePage(QListWidgetItem *current, QListWidgetItem *previous)
 {
     if (!current)
         current = previous;

     m_pagesWidget->setCurrentIndex(m_contentsWidget->row(current));
 }
