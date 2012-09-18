#ifndef LAUNCHENTRYSETTINGSWIDGET_H
#define LAUNCHENTRYSETTINGSWIDGET_H

#include <QWidget>
#include <QVariantList>

class LaunchEntrySettingsWidget : public QWidget
{
    Q_OBJECT
public:
    enum LaunchEntryType{
        Executable = 0,
        Url,
        Script
    };
    explicit LaunchEntrySettingsWidget(QWidget *parent = 0);
    
signals:
    
public slots:
private:
    QMap<QString,QVariantList> *m_launcherEntries;
    
};

#endif // LAUNCHENTRYSETTINGSWIDGET_H
