#ifndef CLEANERTOOLBAR_H
#define CLEANERTOOLBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QVBoxLayout>

class CleanerToolButton;

class CleanerToolBar : public QWidget
{
    Q_OBJECT
public:
    explicit CleanerToolBar(QWidget *parent = 0);

signals:
    void requestTurnPage(int index);

public slots:
    void turnPage(QString index);

private:
    QList<CleanerToolButton *> m_buttonList;
};

#endif // CLEANERTOOLBAR_H
