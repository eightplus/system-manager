#include "extensionedgewidget.h"
#include "contants.h"

#include <QPainter>
#include <QApplication>
#include <QDebug>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsBlurEffect>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QPushButton>
#include <QLabel>

ExtensionEdgeWidget::ExtensionEdgeWidget(QWidget *parent)
    : QFrame(parent)
    , m_borderColor(Qt::transparent)
    , m_borderRadius(0)
    , m_borderWidth(0)
{
    m_borderColor = QColor(255, 255, 255, 51);
    m_coverBrush = QBrush(QColor(255, 255, 255, 179));

    this->setFixedWidth(EXTENSION_EDGE_WIDGET_WIDTH);
    m_contentLayout = new QHBoxLayout(this);
    m_contentLayout->setContentsMargins(0, 0, 0, 0);
    m_contentLayout->setSpacing(0);


    QWidget *w = new QWidget;
    w->setAttribute(Qt::WA_TranslucentBackground);
    QVBoxLayout *l = new QVBoxLayout(w);
    l->setContentsMargins(0, 0, 0, 0);
    QLabel *label = new QLabel;
    label->setText("Extension Edge Widget");
    l->addSpacing(0);
    l->addWidget(label);
    setContentWidget(w);

    QPushButton *hideBtn = new QPushButton();
    hideBtn->setFixedSize(120, 36);
    connect(hideBtn, &QPushButton::clicked, [=] () {
        emit requestHide();
    });
    m_contentLayout->addWidget(hideBtn);
}

void ExtensionEdgeWidget::setPos(const QPoint &pos)
{
    QFrame::move(pos);
}

void ExtensionEdgeWidget::moveWithAnimation(int x, int y)
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(500);
    animation->setEasingCurve(QEasingCurve::InOutCubic);
    animation->setStartValue(pos());
    animation->setEndValue(QPoint(x, y));
    animation->start();
    connect(this, &ExtensionEdgeWidget::requestStopAnimation, animation, &QPropertyAnimation::stop);
    connect(this, &ExtensionEdgeWidget::requestStopAnimation, animation, &QPropertyAnimation::deleteLater);
    connect(animation, &QPropertyAnimation::finished, animation, &QPropertyAnimation::deleteLater);
}

void ExtensionEdgeWidget::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape) {
        this->close();
        return;
    }
    QFrame::keyPressEvent(e);
}

void ExtensionEdgeWidget::mousePressEvent(QMouseEvent *event)
{
    m_dragPos = event->globalPos() - mapToGlobal(QPoint(0, 0));

    QFrame::mousePressEvent(event);
}

void ExtensionEdgeWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_moveEnable) {
        this->move(event->globalPos() - m_dragPos);
    }
    QFrame::mouseMoveEvent(event);
}

void ExtensionEdgeWidget::setContentWidget(QWidget *w)
{
    if (w) {
        QLayoutItem *child;
        if ((child = m_contentLayout->takeAt(0)) != 0) {
            if (child->widget())
                child->widget()->deleteLater();
            delete child;
        }

        m_widget = w;
        updateRectWithContent();
        m_contentLayout->addWidget(w);
    }
}

void ExtensionEdgeWidget::updateRectWithContent()
{
    if (m_widget) {
        resize(qMax(m_widget->sizeHint().width(), EXTENSION_EDGE_WIDGET_WIDTH), height());
    }
}

void ExtensionEdgeWidget::paintEvent(QPaintEvent *e)
{
    QFrame::paintEvent(e);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPainterPath borderPath;
    borderPath.addRoundedRect(this->rect(), m_borderRadius, m_borderRadius);
    QPen pen(m_borderColor, m_borderWidth);
    painter.setPen(pen);
    painter.drawPath(borderPath);

    QRect insideRect;
    insideRect.setRect(this->rect().x() + m_borderWidth, this->rect().y() + m_borderWidth,
                       this->rect().width() - m_borderWidth * 2, this->rect().height() - m_borderWidth * 2);
    QPainterPath insidePath;
    insidePath.addRoundedRect(insideRect, m_borderRadius, m_borderRadius);
    painter.setClipPath(insidePath);
    painter.fillRect(0, 0, width(), height(), m_coverBrush);

    painter.end();
}
