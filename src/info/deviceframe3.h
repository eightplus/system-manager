#ifndef DEVICEFRAME3_H
#define DEVICEFRAME3_H

#include <QFrame>

class QVBoxLayout;

class DeviceFrame3 : public QFrame
{
    Q_OBJECT
public:
    explicit DeviceFrame3(QWidget *parent = 0);

private:
    void initContent();

private:
    QVBoxLayout *m_layout;
};

#endif // DEVICEFRAME3_H
