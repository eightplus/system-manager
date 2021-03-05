#ifndef RESULTWIDGET_H
#define RESULTWIDGET_H

#include <QWidget>

class QLabel;

class ResultWidget : public QWidget
{
    Q_OBJECT
public:
    ResultWidget(QWidget *parent = 0);

signals:
    void cancelled();

private:
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QLabel *m_label;
};

#endif // RESULTWIDGET_H
