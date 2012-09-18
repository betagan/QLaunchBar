#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QDialog>

class QListWidget;
class QListWidgetItem;
class QStackedWidget;

class SettingsWidget : public QDialog
{
    Q_OBJECT
public:
    SettingsWidget();

public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);

private:
    void createIcons();

    QListWidget *m_contentsWidget;
    QStackedWidget *m_pagesWidget;
};

#endif // SETTINGSWIDGET_H
