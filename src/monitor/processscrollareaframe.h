#ifndef PROCESSSCROLLAREAFRAME_H
#define PROCESSSCROLLAREAFRAME_H

#include <QWidget>
#include <QScrollArea>

#include "../basescrollwidget.h"

class QVBoxLayout;
class QStackedWidget;


class ProcessScrollAreaFrame : public BaseScrollWidget
{
    Q_OBJECT

public:
    explicit ProcessScrollAreaFrame(QWidget *parent = 0);
    ~ProcessScrollAreaFrame();

    /*const */QString title() /*const */Q_DECL_OVERRIDE;
    void setTitle(const QString &title) Q_DECL_OVERRIDE;

};

//class ProcessScrollAreaFrame : public QWidget
//{
//    Q_OBJECT
//public:
//    explicit ProcessScrollAreaFrame(QWidget *parent);

//private:
//    void initScrollArea();

//private:
//    QScrollArea *m_area;
//    QVBoxLayout *m_layout;
//    QStackedWidget *m_stackWidget;
//};

#endif // PROCESSSCROLLAREAFRAME_H
