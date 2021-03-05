#pragma once

#include <QFrame>

class QLabel;
class QPushButton;

class RightPanel : public QFrame
{
    Q_OBJECT
public:
    explicit RightPanel(QWidget *parent = 0);

signals:
    void requestHide();

public slots:
    void slot_hide_panel();
    void onBtAddClicked();
    void slot_panel_delay();

protected:
    virtual void focusOutEvent(QFocusEvent *event) Q_DECL_OVERRIDE;
    virtual void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    QLabel *m_label;
    QPushButton *m_btn;
    QBrush m_background;
    QColor m_borderColor;
    int m_radius;
};
