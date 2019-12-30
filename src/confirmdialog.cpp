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

#include "confirmdialog.h"

#include <QPushButton>
#include <QDesktopServices>
#include <QMouseEvent>
#include <QPoint>
#include <QLabel>

ConfirmDialog::ConfirmDialog(const QString &title, const QString &text, QWidget *parent, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
    : QDialog(parent)
    , m_mainLayout(new QVBoxLayout(this))
    , m_buttonBox(new QDialogButtonBox(this))
    , m_iconLabel(new QLabel(this))
    , m_titleLabel(new QLabel(this))
    , m_msgLabel(new QLabel(this))
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint | Qt::Tool);
    this->setStyleSheet("QDialog{border: 1px solid #121212;border-radius:1px;background-color:#1f1f1f;}");

    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setStyleSheet("QLabel{background:transparent;font-size:14px;color:#999999;font-family:方正黑体_GBK;}");//font-weight:bold;
    m_titleLabel->setText(title);

    QHBoxLayout *titleLayout = new QHBoxLayout();
    titleLayout->addWidget(m_titleLabel);
    titleLayout->addStretch();
    titleLayout->setMargin(0);
    titleLayout->setContentsMargins(5,0,0,0);

    m_buttonBox->setStandardButtons(QDialogButtonBox::StandardButtons(int(buttons)));

    QPushButton *okBtn = m_buttonBox->button(QDialogButtonBox::Ok);
    if (okBtn != NULL) {
        okBtn->setFixedSize(91, 25);
        okBtn->setText(tr("Ok"));
        okBtn->setFocusPolicy(Qt::NoFocus);
        okBtn->setStyleSheet("QPushButton{font-size:12px;background:#0f0f0f;border:1px solid #0a9ff5;color:#999999;}QPushButton:hover{background-color:#0a9ff5;border:1px solid #2db0f6;color:#ffffff;} QPushButton:pressed{background-color:#0993e3;border:1px solid #0a9ff5;color:#ffffff;}");
    }

    QPushButton *cancelBtn = m_buttonBox->button(QDialogButtonBox::Cancel);
    if (cancelBtn != NULL) {
        cancelBtn->setFixedSize(91, 25);
        cancelBtn->setText(tr("Cancel"));
        cancelBtn->setFocusPolicy(Qt::NoFocus);
        cancelBtn->setStyleSheet("QPushButton{font-size:12px;background:#0f0f0f;border:1px solid #000000;color:#999999;}QPushButton:hover{background-color:#1f1f1f;border:1px solid #0f0f0f;color:#ffffff;} QPushButton:pressed{background-color:#0d0d0d;border:1px solid #000000;color:#ffffff;}");
    }

    QPushButton *yesBtn = m_buttonBox->button(QDialogButtonBox::Yes);
    if (yesBtn != NULL) {
        yesBtn->setFixedSize(91, 25);
        yesBtn->setText(tr("Yes"));
        yesBtn->setFocusPolicy(Qt::NoFocus);
        yesBtn->setStyleSheet("QPushButton{font-size:12px;background:#0f0f0f;border:1px solid #0a9ff5;color:#999999;}QPushButton:hover{background-color:#0a9ff5;border:1px solid #2db0f6;color:#ffffff;} QPushButton:pressed{background-color:#0993e3;border:1px solid #0a9ff5;color:#ffffff;}");
    }

    QPushButton *noBtn = m_buttonBox->button(QDialogButtonBox::No);
    if (noBtn != NULL) {
        noBtn->setFixedSize(91, 25);
        noBtn->setText(tr("No"));
        noBtn->setFocusPolicy(Qt::NoFocus);
        noBtn->setStyleSheet("QPushButton{font-size:12px;background:#0f0f0f;border:1px solid #000000;color:#999999;}QPushButton:hover{background-color:#1f1f1f;border:1px solid #0f0f0f;color:#ffffff;} QPushButton:pressed{background-color:#0d0d0d;border:1px solid #000000;color:#ffffff;}");
    }

    m_msgLabel->setMinimumWidth(100);
    m_msgLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_msgLabel->setStyleSheet("QLabel{background:transparent;font-size:12px;color:#999999;font-family:方正黑体_GBK;}");//font-weight:bold;
    m_msgLabel->setOpenExternalLinks(true);
    m_msgLabel->setText(text);

    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->setMargin(0);
    hlayout->setContentsMargins(30,0,30,0);
    hlayout->setSpacing(30);
    hlayout->addStretch();
    hlayout->addWidget(m_iconLabel);
    hlayout->addWidget(m_msgLabel);
    hlayout->addStretch();

    QHBoxLayout *blayout = new QHBoxLayout();
    blayout->addStretch();
    blayout->addWidget(m_buttonBox);
    blayout->setContentsMargins(10,0,10,0);

    m_mainLayout->addLayout(titleLayout);
    m_mainLayout->addLayout(hlayout);
    m_mainLayout->addLayout(blayout);
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(10);
    m_mainLayout->setContentsMargins(0, 0, 0, 10);

    this->layout()->setSizeConstraint(QLayout::SetFixedSize);

    this->setIcon(":/res/warn.png");

    connect(m_buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));
}

ConfirmDialog::~ConfirmDialog()
{
}

QAbstractButton *ConfirmDialog::clickedButton() const
{
    return m_clickedBtn;
}


void ConfirmDialog::setDialogSize(int w, int h)
{
    this->setFixedSize(w, h);
}

void ConfirmDialog::setIcon(const QString &icon)
{
    QPixmap pixmap(icon);
    m_iconLabel->setPixmap(pixmap);
    m_iconLabel->adjustSize();
    //m_iconLabel->setFixedSize(pixmap.size());
}

QMessageBox::StandardButton ConfirmDialog::standardButton(QAbstractButton *button) const
{
    return (QMessageBox::StandardButton)m_buttonBox->standardButton(button);
}

void ConfirmDialog::onButtonClicked(QAbstractButton *button)
{
    m_clickedBtn = button;
    int ret = m_buttonBox->standardButton(button);
    done(ret);
}
