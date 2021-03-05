#ifndef DEVICEFRAME1_H
#define DEVICEFRAME1_H

#include <QFrame>

class QVBoxLayout;

class DeviceFrame1 : public QFrame
{
    Q_OBJECT
public:
    explicit DeviceFrame1(QWidget *parent = 0);

private:
    void initContent();

private:
    QVBoxLayout *m_layout;
};

#endif // DEVICEFRAME1_H
