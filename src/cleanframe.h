#ifndef CLEANFRAME_H
#define CLEANFRAME_H

#include <QFrame>

class QVBoxLayout;
class QHBoxLayout;
class QStackedWidget;
class CleanerToolBar;
class CacheFrame;
class CookieFrame;
class HistoryFrame;

class CleanFrame : public QFrame
{
    Q_OBJECT
public:
    explicit CleanFrame(QWidget *parent = 0);
    ~CleanFrame();

    void initUI();

public slots:
    void onTurnPage(int index);

private:
    QVBoxLayout *m_layout;
    QStackedWidget *m_stackWidget;
    CleanerToolBar *title_widget;
    CacheFrame *m_cacheFrame;
    CookieFrame *m_cookieFrame;
    HistoryFrame *m_historyFrame;
};

#endif // CLEANFRAME_H
