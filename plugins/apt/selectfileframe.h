#ifndef SELECTFILEFRAME_H
#define SELECTFILEFRAME_H

#include <QFrame>

class QVBoxLayout;

class SelectFileFrame : public QFrame
{
    Q_OBJECT
public:
    explicit SelectFileFrame(QWidget *parent = 0);

private:
    void initContent();

private:
    QVBoxLayout *m_layout;
};

#endif // SELECTFILEFRAME_H
