#ifndef AUTOSTARTWIDGET_H
#define AUTOSTARTWIDGET_H

#include <QWidget>

class QPushButton;
class QLabel;
class AutoStartView;
class AutoStartModel;
class AutoStartDelegate;

class AutoStartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AutoStartWidget(QWidget* parent = 0);

    void initConnections();

private:
    QPushButton *m_clearAllButton = nullptr;
    QLabel *m_tipLabel = nullptr;
    AutoStartView *m_autostartView = nullptr;
    AutoStartModel *m_autostartModel = nullptr;
    AutoStartDelegate *m_autostartDelegate = nullptr;
};

#endif // AUTOSTARTWIDGET_H
