#include "launchentrysettingswidget.h"
#include <QtGui>

#define LAUNCHER_DATA_SIZE 3

LaunchEntrySettingsWidget::LaunchEntrySettingsWidget(QWidget *parent) :
    QWidget(parent)
{
    QGroupBox *dataGroup = new QGroupBox(tr("Launcher data"));
    QGroupBox *listGroup = new QGroupBox(tr("Installed Launcher"));
    QGridLayout *listLayout = new QGridLayout;

    QListWidget *launcherList = new QListWidget;
    listLayout->addWidget(launcherList);
    listGroup->setLayout(listLayout);


    m_launcherEntries = new QMap<QString,QVariantList>();


    QSettings settings("QLaunchBar.ini", QSettings::IniFormat);

    QVariantList launcherNames = settings.value("launcherNames").toList();
    foreach (QVariant v, launcherNames)
    {
        QVariantList launcherData = settings.value("launcherEntries/"+v.toString()).toList();
        if (launcherData.size() != LAUNCHER_DATA_SIZE)
        {
            qWarning() << "Warning: Corrupted LauncherEntry in INI-File for key: " << v.toString() << "! Skipping.. ";
            continue;
        }
        QListWidgetItem *item = new QListWidgetItem(launcherList);
        item->setText(v.toString());
        m_launcherEntries->insert(v.toString(), launcherData);
    }


    QStackedWidget *dataWidget = new QStackedWidget;
    QWidget *executableWidget = new QWidget;
    QWidget *urlWidget = new QWidget;
    QWidget *scriptWidget = new QWidget;

    // common for all Widgets on the stack

    QLabel *nameLabel = new QLabel(tr("Name:"));
    QLineEdit *nameEdit = new QLineEdit;

    QPushButton *saveButton = new QPushButton(QIcon(":/DefaultIcons/saveIcon"), tr("&Save"));
    QPushButton *undoButton = new QPushButton(QIcon(":/DefaultIcons/undoIcon"), tr("&Undo changes"));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(undoButton);
    buttonLayout->addWidget(saveButton);


    QLabel *iconLabel = new QLabel(tr("Icon:"));
    QLineEdit *iconEdit = new QLineEdit;
    QPushButton *iconButton = new QPushButton(QIcon(":/DefaultIcons/folderIcon"), tr("Browse"));

    // executable widget

    QLabel *pathLabel = new QLabel(tr("Executable path"));
    QLineEdit *pathEdit = new QLineEdit;
    QPushButton *pathButton = new QPushButton(QIcon(":/DefaultIcons/folderIcon"), tr("Browse"));

    QLabel *iconHintLabel = new QLabel(tr("If you leave the Icon-Box blank, "
                                          "QLaunchBar will display the executable's icon instead."));
    //iconHintLabel->setWordWrap(true);

    QVBoxLayout *exeVLayout = new QVBoxLayout;
    QGridLayout *executableLayout = new QGridLayout;
    executableLayout->addWidget(nameLabel,0,0);
    executableLayout->addWidget(nameEdit,0,1);
    executableLayout->addWidget(iconLabel,1,0);
    executableLayout->addWidget(iconEdit,1,1);
    executableLayout->addWidget(iconButton,1,2);
    executableLayout->addWidget(pathLabel,2,0);
    executableLayout->addWidget(pathEdit,2,1);
    executableLayout->addWidget(pathButton,2,2);
    executableLayout->addWidget(iconHintLabel,3,0,3,3);

    exeVLayout->addLayout(executableLayout);
    exeVLayout->addStretch();
    exeVLayout->addLayout(buttonLayout);
    executableWidget->setLayout(exeVLayout);

    dataWidget->addWidget(executableWidget);
    dataWidget->setCurrentIndex(0);

    QGridLayout *dataLayout = new QGridLayout;
    dataLayout->addWidget(dataWidget);

    dataGroup->setLayout(dataLayout);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(listGroup);
    mainLayout->addSpacing(5);
    mainLayout->addWidget(dataGroup);
    setLayout(mainLayout);
}
