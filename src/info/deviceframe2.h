#ifndef DEVICEFRAME2_H
#define DEVICEFRAME2_H

#include <QFrame>

class QVBoxLayout;

class DeviceFrame2 : public QFrame
{
    Q_OBJECT
public:
    explicit DeviceFrame2(QWidget *parent = 0);

private:
    void initContent();

private:
    QVBoxLayout *m_layout;
};

#endif // DEVICEFRAME2_H
