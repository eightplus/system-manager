#include "protest1.h"
#include "titleheader.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

ProFrame1::ProFrame1(QWidget *parent)
    :QFrame(parent)
{
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(10);

    TitleHeader *title = new TitleHeader(tr("My header 001"));
    m_layout->addWidget(title);

    initContent1();
    initContent2();
}

void ProFrame1::initContent1()
{
    QLabel *title = new QLabel(tr("Content 1"));
    m_layout->addSpacing(10);
    m_layout->addWidget(title);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->setContentsMargins(0, 0, 0, 0);
    hlayout->setSpacing(7);
    hlayout->addStretch();

    QLabel *label = new QLabel;
    label->setText("aaaaa");
    hlayout->addWidget(label);

    label = new QLabel;
    label->setText("bbbbb");
    hlayout->addWidget(label);

    hlayout->addStretch();

    m_layout->addLayout(hlayout);
}

void ProFrame1::initContent2()
{
    QLabel *title = new QLabel(tr("Content 2"));
    m_layout->addSpacing(20);
    m_layout->addWidget(title);

    QPushButton *btn = new QPushButton(this);
    btn->setText("click me");
    btn->setFixedSize(120, 26);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->setContentsMargins(0, 0, 0, 0);
    hlayout->setSpacing(50);
    hlayout->addWidget(new QLabel(tr("Sub Content")));
    hlayout->addWidget(btn);
    hlayout->addStretch();

    m_layout->addLayout(hlayout);
    m_layout->addStretch();
}
