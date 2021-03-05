#include "protest2.h"
#include "titleheader.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include <QDebug>

ProFrame2::ProFrame2(QWidget *parent)
    :QFrame(parent)
{
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 20, 0, 0);
    m_layout->setSpacing(0);

    TitleHeader *title = new TitleHeader(tr("My header 002"));
    m_layout->addWidget(title);

    initContent1();
    initContent2();
    initContent3();
}

void ProFrame2::initContent1()
{
    QLabel *title = new QLabel(tr("Content 1"));
    m_layout->addSpacing(10);
    m_layout->addWidget(title);
    m_layout->addSpacing(10);

    QHBoxLayout *layout = new QHBoxLayout;
    m_layout->addSpacing(10);
    layout->setContentsMargins(0, 0, 0, 0);
    QFormLayout *formlayout = new QFormLayout;
    formlayout->setVerticalSpacing(10);
    formlayout->setHorizontalSpacing(50);
    formlayout->setContentsMargins(0, 0, 0, 0);
    formlayout->setLabelAlignment(Qt::AlignLeft);
    layout->addLayout(formlayout);

    QStringList list;
    list << "aa" << "bb" << "cc" << "dd" << "ee" << "ff";
    for (int i=0 ;i < list.length(); i++) {
        QLabel *label = new QLabel;
        label->setText(QString::number(i));
        formlayout->addRow(new QLabel(list.at(i)), label);
    }

    m_layout->addLayout(layout);
}

void ProFrame2::initContent2()
{
    QLabel *title = new QLabel(tr("Content 2"));
    m_layout->addSpacing(10);
    m_layout->addWidget(title);
    m_layout->addSpacing(10);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setSpacing(10);
    layout->setContentsMargins(0, 0, 0, 0);
    QFormLayout *formlayout = new QFormLayout;
    formlayout->setVerticalSpacing(10);
    formlayout->setHorizontalSpacing(50);
    formlayout->setContentsMargins(0, 0, 0, 0);
    formlayout->setLabelAlignment(Qt::AlignLeft);
    layout->addLayout(formlayout);

    QStringList list;
    list << "lixiang" << "kobe" << "ljy";
    for (int i=0 ;i < list.length(); i++) {
        QLabel *label = new QLabel;
        label->setText(QString::number(i));
        formlayout->addRow(new QLabel(list.at(i)), label);
    }

    m_layout->addLayout(layout);
}

void ProFrame2::initContent3()
{
    QPushButton *backBtn = new QPushButton(tr("Back"));
    backBtn->setFixedSize(180, 36);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setAlignment(Qt::AlignHCenter);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(backBtn);
    m_layout->addLayout(layout);
}
