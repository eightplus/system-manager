#ifndef MONITORBASEWIDGET_H
#define MONITORBASEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class QStackedWidget;
class QScrollArea;

class MonitorBaseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MonitorBaseWidget();
    ~MonitorBaseWidget();

    const QString title() const;
    void setTitle(const QString &title);

signals:
    void headerClicked() const;

protected:
    virtual void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    virtual void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;

protected:
    QLabel *m_moduleIcon;
    QLabel *m_moduleTitle;
    QVBoxLayout *m_centralLayout;
//    QLabel *m_titleLabel;
    QScrollArea *m_area;
//    QVBoxLayout *m_layout;
    QVBoxLayout *areaLayout;
    QStackedWidget *m_stackWidget;
};

#endif // MONITORBASEWIDGET_H
