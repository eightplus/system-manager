#pragma once

#include <QScopedPointer>
#include <QFrame>
#include <QLabel>
#include <QPushButton>

class QVBoxLayout;
class TopWidget;
class BottomWidget;

class HomeWidget : public QFrame
{
    Q_OBJECT
public:
    explicit HomeWidget(QWidget *parent = 0);
    ~HomeWidget();

    void showHomePage();

signals:
    void requestBack();
    void requestSubWidget(int index, const QString &name);

private:
    TopWidget      *m_topWidget;
    BottomWidget   *m_bottomToolbar;
    QVBoxLayout *m_layout;
};

