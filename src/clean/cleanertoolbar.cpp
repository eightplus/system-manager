#include "cleanertoolbar.h"
#include "cleanertoolbutton.h"

CleanerToolBar::CleanerToolBar(QWidget *parent)
    : QWidget(parent)
{
//    QSizePolicy sp(QSizePolicy::Expanding, QSizePolicy::Fixed);
//    sp.setHorizontalStretch(1000);
//    this->setSizePolicy(sp);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setFixedHeight(110);

    this->setAutoFillBackground(true);
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, QColor("#eff4fa"));
    this->setPalette(palette);

    QStringList string_list;
    string_list << ":/res/info1.png" << ":/res/info2.png" << ":/res/info3.png";

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setSpacing(5);
    layout->setContentsMargins(15, 0, 15, 0);
    QSignalMapper *signal_mapper = new QSignalMapper(this);

    for (int i=0; i<string_list.size(); i++) {
        CleanerToolButton *tool_button = new CleanerToolButton(string_list.at(i));
        m_buttonList.append(tool_button);
        connect(tool_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
        signal_mapper->setMapping(tool_button, QString::number(i, 10));
        layout->addWidget(tool_button, 0, Qt::AlignBottom);
    }
    connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(turnPage(QString)));
    layout->addStretch();

    this->setLayout(layout);

    m_buttonList.at(0)->setText(tr("Cache"));
    m_buttonList.at(1)->setText(tr("Cookie"));
    m_buttonList.at(2)->setText(tr("History"));
}

void CleanerToolBar::turnPage(QString index)
{
    bool ok;
    int currentIndex = index.toInt(&ok, 10);

    for (int i=0; i<m_buttonList.count(); i++) {
        CleanerToolButton *btn = m_buttonList.at(i);
        if(currentIndex == i) {
            btn->setMousePressed(true);
        }
        else {
            btn->setMousePressed(false);
        }
    }

    emit requestTurnPage(currentIndex);
}
