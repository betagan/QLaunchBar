#ifndef LAUNCHBUTTON_H
#define LAUNCHBUTTON_H

#include <QPushButton>

class LaunchButton : public QPushButton
{
    Q_OBJECT
public:
    LaunchButton(QString name, QString path, QIcon icon, QWidget *parent = 0);
    void resize(const QSize &);

signals:
    void mouseMoved();
protected:
    void mouseMoveEvent(QMouseEvent *event);

public slots:

private slots:
    void onButtonClicked();

private:
    QString m_path;
    QString m_name;
};

#endif // LAUNCHBUTTON_H
