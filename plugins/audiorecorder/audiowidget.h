#ifndef AUDIOWIDGET_H
#define AUDIOWIDGET_H

#include <QWidget>

class QPushButton;

class AudioWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AudioWidget(QWidget* parent = 0);

signals:
    void requestFinish();

private:
    QPushButton *m_okBtn;
};

#endif // AUDIOWIDGET_H
