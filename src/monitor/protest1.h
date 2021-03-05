#ifndef PROTESFRAME1_H
#define PROTESFRAME1_H

#include <QFrame>

class QVBoxLayout;

class ProFrame1 : public QFrame
{
    Q_OBJECT
public:
    explicit ProFrame1(QWidget *parent = 0);

private:
    void initContent1();
    void initContent2();

private:
    QVBoxLayout *m_layout;
};

#endif // PROTESFRAME1_H
