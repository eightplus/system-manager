#ifndef INSTALLFRAME_H
#define INSTALLFRAME_H

#include <QFrame>

class QVBoxLayout;

class InstallFrame : public QFrame
{
    Q_OBJECT
public:
    explicit InstallFrame(QWidget *parent = 0);

private:
    void initContent();

private:
    QVBoxLayout *m_layout;
};

#endif // INSTALLFRAME_H
