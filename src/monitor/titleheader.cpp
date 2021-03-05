#include "titleheader.h"

#include <QFontMetrics>
#include <QPainter>

TitleHeader::TitleHeader(const QString &title, QWidget *parent)
    : QWidget(parent)
    , m_title(title)
{
    setFixedHeight(24);
}

void TitleHeader::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    QFont f;
    f.setWeight(QFont::DemiBold);
    f.setPixelSize(14);

    const int w = QFontMetrics(f).width(m_title);
    const int h = QFontMetrics(f).height();

    const QRect textRect(20, 0, w, h);
    const int space = textRect.x() + textRect.width() + 10;
    const QRect colorRect(space, (height() - 1) / 2, width() - space - 20, 1);

    QPainter painter(this);
    painter.setFont(f);
    painter.setPen(QPen(QColor("#303030")));
    painter.drawText(textRect, m_title);

    painter.fillRect(colorRect, QColor(0, 0, 0, 25));
}
