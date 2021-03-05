#ifndef BOTTOMWIDGET_H
#define BOTTOMWIDGET_H

#include <QWidget>

class QPushButton;

class BottomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BottomWidget(QWidget *parent = 0);

signals:
    void infoBtnClicked();
    void monitorBtnClicked();
    void cleanBtnClicked();
    void toolsBtnClicked();

private:
    void initUI();
    void initConnect();

private:
    QPushButton *m_infoButton = nullptr;
    QPushButton *m_monitorButton = nullptr;
    QPushButton *m_cleanButton = nullptr;
    QPushButton *m_toolsButton = nullptr;
};

#endif // BOTTOMWIDGET_H
