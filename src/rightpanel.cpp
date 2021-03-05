#include "rightpanel.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFocusEvent>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QPainter>

RightPanel::RightPanel(QWidget *parent) : QFrame(parent)
  , m_radius(4)
  , m_borderColor(QColor(0, 0, 0, 255 / 10))
  , m_background(QBrush(QColor(6,54,56,85)))
{
    setObjectName("RightPanel");
    //this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    QVBoxLayout *layout = new QVBoxLayout(this);
    setFocusPolicy(Qt::ClickFocus);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(15);

    m_label = new QLabel;
    m_label->setText("Slide Right");

//    QSizePolicy sp(QSizePolicy::Preferred, QSizePolicy::Preferred);
//    sp.setVerticalStretch(100);
//    m_label->setSizePolicy(sp);

    m_btn = new QPushButton;
    m_btn->setText("test right panel");

    layout->addWidget(m_label, 0, Qt::AlignHCenter);
    layout->addWidget(m_btn, 0, Qt::AlignHCenter);
    layout->addStretch();

    connect(m_btn, SIGNAL(clicked(bool)), this, SLOT(onBtAddClicked()));
}

void RightPanel::onBtAddClicked()
{
    QTimer::singleShot(500, this, SLOT(slot_panel_delay()));
}

void RightPanel::slot_panel_delay()
{
    emit this->requestHide();
}

void RightPanel::focusOutEvent(QFocusEvent *event)
{
    // TODO: monitor mouse position
    QPoint mousePos = mapToParent(mapFromGlobal(QCursor::pos()));
//    qDebug() << mapFromGlobal(QCursor::pos()) << mousePos;
//    qDebug() << event->reason();
    if (!this->geometry().contains(mousePos)) {
        if (event && event->reason() == Qt::MouseFocusReason) {
            QTimer::singleShot(50, this, SLOT(slot_hide_panel()));
        }
    }
    QFrame::focusOutEvent(event);
}

void RightPanel::slot_hide_panel()
{
    qDebug() << "self lost focus hide";
    emit this->requestHide();
}

void RightPanel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);

    QBrush background =  this->m_background;
    QColor borderColor = this->m_borderColor;

    //arcTo(rect, 45,315);//即在矩形rect内，起始角度为45，逆时针转315度形成的弧
    //arcTo(rect, 45,-315);//即在矩形rect内，起始角度为45，顺时针转315度形成的弧
    const int triangleOffset = 30;
    const qreal radius = this->m_radius;
    const qreal triangleHeight = 8;
    const qreal triangleWidth = 3;

    QPainterPath path;
    QRect rect = this->rect();
    int cornerSize = radius*2;//调节圆角的大小

    path.moveTo(rect.left() + m_radius, rect.top());
    path.arcTo(rect.left(), rect.top(), cornerSize, cornerSize, 90.0f, 90.0f);

    path.lineTo(rect.left(), rect.bottom() - m_radius);
    path.arcTo(rect.left(), rect.bottom() - cornerSize, cornerSize, cornerSize, 180.0f, 90.0f);

    path.lineTo(rect.right() - triangleWidth - m_radius, rect.bottom());
    path.arcTo(rect.right()- triangleWidth - cornerSize, rect.bottom() - cornerSize, cornerSize, cornerSize, 270.0f, 90.0f);

    path.lineTo(rect.right()- triangleWidth, rect.height() / 2 + triangleHeight/2 + triangleOffset);
    path.lineTo(rect.right(), rect.height() / 2 + triangleOffset);
    path.lineTo(rect.right()- triangleWidth, rect.height() / 2 + triangleOffset - triangleHeight/2);
    path.lineTo(rect.right()- triangleWidth, m_radius);

    path.arcTo(rect.right() - triangleWidth - cornerSize, rect.top(), cornerSize, cornerSize, 0.0f, 90.0f);
    path.lineTo(rect.left() + m_radius, rect.top());

    painter.fillPath(path, background);

    QPen pen(borderColor);
    pen.setWidth(1);
    painter.strokePath(path, pen);
}
