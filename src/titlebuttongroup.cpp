#include "titlebuttongroup.h"
#include "systembutton.h"

#include <QHBoxLayout>

TitleButtonGroup::TitleButtonGroup(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *hLayout = new QHBoxLayout;

    menu_btn = new SystemButton();
    connect(menu_btn, SIGNAL(clicked(bool)), this, SIGNAL(showMenu()));

    minimun_btn = new SystemButton();
    connect(minimun_btn, SIGNAL(clicked(bool)), this, SIGNAL(showMin()));

    maximum_btn = new SystemButton();
    connect(maximum_btn, SIGNAL(clicked(bool)), this, SIGNAL(showMax()));

    clost_btn = new SystemButton();
    connect(clost_btn, SIGNAL(clicked(bool)), this, SIGNAL(requestQuit()));

    menu_btn->loadPixmap(":/res/sysbutton/menu.png", ":/res/sysbutton/menu_hover.png", ":/res/sysbutton/menu_hover.png");
    menu_btn->setObjectName("title_btn_menu");
    maximum_btn->loadPixmap(":/res/sysbutton/max.png", ":/res/sysbutton/max_hover.png", ":/res/sysbutton/max_hover.png");
    maximum_btn->setObjectName("title_btn_maxmun");
    minimun_btn->loadPixmap(":/res/sysbutton/min.png", ":/res/sysbutton/min_hover.png", ":/res/sysbutton/min_hover.png");
    minimun_btn->setObjectName("title_btn_minimun");
    clost_btn->loadPixmap(":/res/sysbutton/close.png", ":/res/sysbutton/close_hover.png", ":/res/sysbutton/close_hover.png");
    clost_btn->setObjectName("title_btn_close");

    hLayout->addWidget(menu_btn);
    hLayout->addWidget(minimun_btn);
    hLayout->addWidget(maximum_btn);
    hLayout->addWidget(clost_btn);
    hLayout->setContentsMargins(5, 0, 5, 0);
    hLayout->setSpacing(0);

    this->setLayout(hLayout);
}

void TitleButtonGroup::updateMaxIcon(bool b)
{
    if (b) {
        maximum_btn->loadPixmap(":/res/sysbutton/max.png", ":/res/sysbutton/max_hover.png", ":/res/sysbutton/max_hover.png");
    }
    else {
        maximum_btn->loadPixmap(":/res/sysbutton/unmax.png", ":/res/sysbutton/unmax_hover.png", ":/res/sysbutton/unmax_hover.png");
    }
}
