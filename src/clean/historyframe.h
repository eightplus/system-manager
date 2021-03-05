#ifndef HISTORYFRAME_H
#define HISTORYFRAME_H

#include <QFrame>

class QVBoxLayout;

class HistoryFrame : public QFrame
{
    Q_OBJECT
public:
    explicit HistoryFrame(QWidget *parent = 0);

private:
    void initContent();

private:
    QVBoxLayout *m_layout;
};

#endif // HISTORYFRAME_H
