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

#ifndef CONFIRMDIALOG_H_
#define CONFIRMDIALOG_H_

#include "utils.h"

#include <QString>
#include <QMessageBox>
#include <QGridLayout>
#include <QDialogButtonBox>

class QPushButton;

class ConfirmDialog : public QDialog
{
    Q_OBJECT

public:
    ConfirmDialog(const QString &title, const QString &text, QWidget *parent = nullptr, QMessageBox::StandardButtons buttons = QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::StandardButton defaultButton = QMessageBox::Ok);
    ~ConfirmDialog();

    QAbstractButton *clickedButton() const;
    QMessageBox::StandardButton standardButton(QAbstractButton *button) const;
    void setIcon(const QString &icon);
    void setDialogSize(int w, int h);

private slots:
    void onButtonClicked(QAbstractButton *button);

private:
    QLabel *m_iconLabel;
    QLabel *m_titleLabel;
    QLabel *m_msgLabel;
    QDialogButtonBox *m_buttonBox;
    QAbstractButton *m_clickedBtn;
    QVBoxLayout *m_mainLayout;
};

#endif // CONFIRMDIALOG_H_
