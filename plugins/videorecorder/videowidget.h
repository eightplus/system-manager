#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>

class QPushButton;

class VideoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VideoWidget(QWidget* parent = 0);

private:
    QPushButton *m_okBtn;
};

#endif // VIDEOWIDGET_H
