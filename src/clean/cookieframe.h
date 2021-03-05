#ifndef COOKIEFRAME_H
#define COOKIEFRAME_H

#include <QFrame>

class QVBoxLayout;

class CookieFrame : public QFrame
{
    Q_OBJECT
public:
    explicit CookieFrame(QWidget *parent = 0);

private:
    void initContent();

private:
    QVBoxLayout *m_layout;
};

#endif // COOKIEFRAME_H
