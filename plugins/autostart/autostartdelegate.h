#ifndef AUTOSTARTDELEGATE_H
#define AUTOSTARTDELEGATE_H

#include <QStyledItemDelegate>

class AutoStartDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    AutoStartDelegate(QObject *parent = nullptr);

signals:
    void removeBtnClicked() const;

public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // AUTOSTARTDELEGATE_H
