#ifndef BASESCROLLWIDGET_H
#define BASESCROLLWIDGET_H

#include <QWidget>

class QVBoxLayout;
class QStackedWidget;
class QScrollArea;
class QLabel;

class BaseScrollWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BaseScrollWidget(QWidget *parent = 0);
    ~BaseScrollWidget();

    virtual QString title() = 0;
    virtual void setTitle(const QString &title) = 0;

protected:
    virtual void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    virtual void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;

protected:
    QLabel *m_titleLabel;
    QScrollArea *m_area;
    QVBoxLayout *m_layout;
    QVBoxLayout *areaLayout;
    QStackedWidget *m_stackWidget;
};

#endif // BASESCROLLWIDGET_H
