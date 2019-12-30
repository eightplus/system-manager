/*
 * Copyright (C) 2019 ~ 2020 kobe24_lixiang@126.com
 *
 * Authors:
 *  lixiang    kobe24_lixiang@126.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "infoitems.h"
#include "label.h"

#include <QFormLayout>
#include <QApplication>
#include <QIcon>
#include <QDebug>

namespace {

const int TITLE_MAXWIDTH = 100;
const int FIELD_MAXWIDTH = 300;
const int CONTENTS_MARGINS = 10;
const int SPACING = 5;

struct TitleMeta {
    QString key;
    const char *name;
};

static TitleMeta titleKeys[] = {
    {"SystemInforamation",              QT_TRANSLATE_NOOP("SysManager", "System Inforamation")},
    {"Size",                            QT_TRANSLATE_NOOP("SysManager", "Size")},
    {"Capacity",                        QT_TRANSLATE_NOOP("SysManager", "Capacity (GB)")},
    {"CpuClock",                        QT_TRANSLATE_NOOP("SysManager", "Cpu Clock")},
    {"CpuSize",                         QT_TRANSLATE_NOOP("SysManager", "Cpu Size")},
    {"CpuSlot",                         QT_TRANSLATE_NOOP("SysManager", "Cpu Slot")},
    {"", ""}
};

static int maxTitleWidth()
{
    int maxWidth = 0;
    QFont font;
    font.setPixelSize(11);
    QFontMetrics fm(font);
    for (const TitleMeta* i = titleKeys; ! i->key.isEmpty(); ++i) {
        maxWidth = qMax(maxWidth + 1, fm.boundingRect(i->name).width());
    }

    return maxWidth;
}

}  // namespace

InfoItems::InfoItems(QWidget *parent)
    : QFrame(parent)
    , m_vendorIconLabel(new QLabel(this))
    , m_formLayout(new QFormLayout)
{
    this->setObjectName("InfoItems");

    m_formLayout->setSpacing(SPACING);
    m_formLayout->setContentsMargins(0, 0, 0, 0);
    m_formLayout->setLabelAlignment(Qt::AlignRight);//设置标签的对齐方式

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(CONTENTS_MARGINS, 0, CONTENTS_MARGINS, 0);
    mainLayout->addLayout(m_formLayout);
    mainLayout->addStretch();
    mainLayout->addWidget(m_vendorIconLabel, 0, Qt::AlignTop);
    this->setLayout(mainLayout);

    m_maxTitleLabelWidth = maxTitleWidth();
    m_maxFieldLabelWidth = 3 * m_maxTitleLabelWidth;//this->width() - m_maxTitleLabelWidth - CONTENTS_MARGINS * 2 - SPACING;
}

InfoItems::~InfoItems()
{
    clearLayout(m_formLayout);
}

void InfoItems::setLogo()
{
    QPixmap m_pixmap = QPixmap(QIcon(":/res/system-manager.png").pixmap(QSize(64, 64)));
    m_vendorIconLabel->setPixmap(m_pixmap);
    m_vendorIconLabel->setFixedSize(m_pixmap.size());
}

void InfoItems::setInfo(const StringMap &result)
{
    for (auto it(result.cbegin()); it != result.cend(); ++it) {
        this->addOneLine(it.key().toStdString().c_str(), it.value().toString());
    }

    this->setLogo();
}

void InfoItems::addOneLine(const char *title, const QString &content)
{
    ContentLabel *fieldItem = new ContentLabel;
    fieldItem->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    fieldItem->setText(content);
    fieldItem->setFixedWidth(qMin(m_maxFieldLabelWidth, FIELD_MAXWIDTH));

    TitleLabel *titleItem = new TitleLabel(myTrFunc(title) + ":");
    titleItem->setMinimumHeight(fieldItem->minimumHeight());
    titleItem->setFixedWidth(qMin(m_maxTitleLabelWidth, TITLE_MAXWIDTH));
    titleItem->setAlignment(Qt::AlignRight | Qt::AlignTop);
    m_formLayout->addRow(titleItem, fieldItem);
    //this->setFixedHeight(m_formLayout->sizeHint().height());
}

void InfoItems::clearLayout(QLayout *layout)
{
    QFormLayout *formLayout = static_cast<QFormLayout *>(layout);
    if (formLayout) {
        for (int i = 0; i < formLayout->rowCount(); i++) {
            QLayoutItem *lableItem = formLayout->itemAt(i, QFormLayout::LabelRole);
            QLayoutItem *fieldItem = formLayout->itemAt(i, QFormLayout::FieldRole);
            if (lableItem) {
                if (lableItem->widget())
                    delete lableItem->widget();
                formLayout->removeItem(lableItem);
            }
            if (fieldItem) {
                if (fieldItem->widget())
                    delete fieldItem->widget();
                formLayout->removeItem(fieldItem);
            }
        }
    }
}

const QString InfoItems::myTrFunc(const char *txt)
{
//    for (const TitleMeta* i = titleKeys; ! i->key.isEmpty(); ++i) {

//    }
    return qApp->translate("SysManager", txt);
}

QString InfoItems::transName(const QString &name)
{
    const QStringList moduleList = { "vendor", "Product", "Version", "Serial", "Size" };
    const QString scope = "SysManager";
    static const QStringList transList = {
        QT_TRANSLATE_NOOP(scope, "Vendor"),
        QT_TRANSLATE_NOOP(scope, "Product"),
        QT_TRANSLATE_NOOP(scope, "Version"),
        QT_TRANSLATE_NOOP(scope, "Serial"),
        QT_TRANSLATE_NOOP(scope, "Size"),
    };

    const int idx = name.isEmpty() ? -1 : moduleList.indexOf(name);

    if (idx == -1)
        return QString();
    else
        return QCoreApplication::translate(scope.toStdString().c_str(), transList[idx].toStdString().c_str());
}

bool InfoItems::event(QEvent *event)
{
    if (event->type() == QEvent::LayoutRequest) {
        this->setFixedHeight(m_formLayout->sizeHint().height());
    }

    return QWidget::event(event);
}
