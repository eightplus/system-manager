#ifndef CLEANERTOOlBUTTON_H
#define CLEANERTOOlBUTTON_H

#include <QToolButton>
#include <QMouseEvent>
#include <QPainter>

class CleanerToolButton : public QToolButton
{
public:
    explicit CleanerToolButton(const QString &icon, QWidget *parent = 0);
    ~CleanerToolButton();

    void setMousePressed(bool b);
    void paintGradientBackground(int topColor, int middleColor, int bottomColor);

protected:
    virtual void enterEvent(QEvent *) Q_DECL_OVERRIDE;
    virtual void leaveEvent(QEvent *) Q_DECL_OVERRIDE;
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

public:
    bool m_mouseHover;
    bool m_mousePressed;
};

#endif //CLEANERTOOlBUTTON_H
