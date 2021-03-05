#include "cleanertoolbutton.h"

CleanerToolButton::CleanerToolButton(const QString &icon, QWidget *parent)
    :QToolButton(parent)
    , m_mouseHover(false)
    , m_mousePressed(false)
{
    this->setStyleSheet("QToolButton{background:transparent;border:none;}");
    this->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    QPalette textPalette = palette();
    textPalette.setColor(QPalette::ButtonText, QColor(0, 0, 0));
    setPalette(textPalette);

    QFont &textFont = const_cast<QFont &>(font());
    textFont.setWeight(QFont::Bold);

    QPixmap pixmap(icon);
    this->setIcon(pixmap);
    this->setIconSize(pixmap.size());

    this->setFixedSize(pixmap.width() + 25, pixmap.height() + 25);
    this->setAutoRaise(true);
}

CleanerToolButton::~CleanerToolButton()
{

}

void CleanerToolButton::enterEvent(QEvent *)
{
    m_mouseHover = true;
}

void CleanerToolButton::leaveEvent(QEvent *)
{
    m_mouseHover = false;
}

void CleanerToolButton::mousePressEvent(QMouseEvent *event)
{
    if (!rect().contains(event->pos())) {
        return;
    }

    event->accept();

    if (event->button() == Qt::LeftButton) {
        emit clicked();
    }
}

void CleanerToolButton::setMousePressed(bool b)
{
    this->m_mousePressed = b;
    this->update();
}

void CleanerToolButton::paintEvent(QPaintEvent *event)
{
    if (m_mouseHover) {
        paintGradientBackground(0, 100, 150);
    }
    else {
        if (m_mousePressed) {
            paintGradientBackground(0, 100, 150);
        }
    }

    QToolButton::paintEvent(event);
}

void CleanerToolButton::paintGradientBackground(int topColor, int middleColor, int bottomColor)
{
    QPainter painter(this);
    QPen pen(Qt::NoBrush, 1);
    painter.setPen(pen);

    QLinearGradient linear(rect().topLeft(), rect().bottomLeft());
    linear.setColorAt(0, QColor(230, 230, 230, topColor));
    linear.setColorAt(0.5, QColor(230, 230, 230, middleColor));
    linear.setColorAt(1, QColor(230, 230, 230, bottomColor));
    painter.setBrush(linear);
    painter.drawRect(rect());
}
