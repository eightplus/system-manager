#ifndef EXTENSIONEDGEWIDGET_H
#define EXTENSIONEDGEWIDGET_H

#include <QHBoxLayout>
#include <QFrame>
#include <QWidget>

class ExtensionEdgeWidget : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(QPoint pos READ pos WRITE setPos)
public:
    explicit ExtensionEdgeWidget(QWidget *parent);
    void setContentWidget(QWidget *w);
    void updateRectWithContent();
    void moveWithAnimation(int x, int y);
    void setPos(const QPoint &pos);

signals:
    void requestStopAnimation();
    void requestHide();

protected:
    void keyPressEvent(QKeyEvent *e) override;
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QColor  m_borderColor;
    int     m_borderRadius;
    int     m_borderWidth;
    QBrush  m_coverBrush;
    QPoint m_dragPos;
    bool m_moveEnable = false;
    QWidget *m_widget;
    QHBoxLayout *m_contentLayout;
};

#endif // EXTENSIONEDGEWIDGET_H
