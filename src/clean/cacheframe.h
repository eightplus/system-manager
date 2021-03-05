#ifndef CACHEFRAME_H
#define CACHEFRAME_H

#include <QFrame>

class QVBoxLayout;

class CacheFrame : public QFrame
{
    Q_OBJECT
public:
    explicit CacheFrame(QWidget *parent = 0);

private:
    void initContent();

private:
    QVBoxLayout *m_layout;
};

#endif // CACHEFRAME_H
