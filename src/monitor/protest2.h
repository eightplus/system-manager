#ifndef PROTESFRAME2_H
#define PROTESFRAME2_H

#include <QFrame>

class QVBoxLayout;

class ProFrame2 : public QFrame
{
    Q_OBJECT
public:
    explicit ProFrame2(QWidget *parent = 0);

private:
    void initContent1();
    void initContent2();
    void initContent3();

private:
    QVBoxLayout *m_layout;
};

#endif // PROTESFRAME2_H
