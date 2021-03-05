#ifndef INFOSCROLLPANEL_H
#define INFOSCROLLPANEL_H

#include <QWidget>
#include <QScrollArea>

class QVBoxLayout;
class QStackedWidget;
class QLabel;

class InfoScrollPanel : public QWidget
{
    Q_OBJECT
public:
    explicit InfoScrollPanel(QWidget *parent = 0);
    ~InfoScrollPanel();

    void addContentWidget(QWidget *w);
    void setTitle(const QString &title);

private:
    void initScrollArea();

private:
    QLabel *m_label;
    QScrollArea *m_area;
    QVBoxLayout *m_layout;
    QStackedWidget *m_stackWidget;
    QVBoxLayout *areaLayout;
};

#endif // INFOSCROLLPANEL_H
