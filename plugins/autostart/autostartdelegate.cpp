#include "autostartdelegate.h"
#include "autostartmodel.h"

#include <QPainter>
#include <QPushButton>

namespace {

static const QSize AutoStartIconSize = QSize(48, 48);

}


AutoStartDelegate::AutoStartDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

void AutoStartDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid()) {
        return;
    }

    const QString &exec = index.data(AutoStartModel::AutoStartExecRole).toString();
    const QString &name = index.data(AutoStartModel::AutoStartNameRole).toString();
    const QString &comment = index.data(AutoStartModel::AutoStartCommentRole).toString();
    const QString &iconName = index.data(AutoStartModel::AutoStartIconRole).toString();
    bool remove = index.data(AutoStartModel::AutoStartRemoveRole).toBool();
    bool hover = index.data(AutoStartModel::AutoStartHoverRole).toBool();
    int removeOffset = index.data(AutoStartModel::AutoStartXOffsetRole).toInt();
    //quint32 removeOffset = static_cast<quint32>(index.data(AutoStartModel::AutoStartXOffsetRole).toInt());

    QRect rect = option.rect;

    // for remove anim
    if (remove) {
        rect.setX(rect.x() + removeOffset);
    }

    // draw hover background color
    if (hover) {
        painter->fillRect(rect, QColor(255, 255, 255, 50));
    }

    // draw icon
    QRect iconRect = QRect(rect.x() + 10, rect.y() + ((rect.height() - AutoStartIconSize.height()) / 2), AutoStartIconSize.width(), AutoStartIconSize.height());
    QPixmap pixmap;
    if (!iconName.isEmpty()) {
        QIcon icon = QIcon(iconName);
        const qreal ratio = painter->device()->devicePixelRatio();
        pixmap = icon.pixmap(AutoStartIconSize * ratio).scaled(AutoStartIconSize * ratio, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        pixmap.setDevicePixelRatio(ratio);
    }
    else {
        QIcon icon = QIcon(":/images/icon.png");
        const qreal ratio = painter->device()->devicePixelRatio();
        pixmap = icon.pixmap(AutoStartIconSize * ratio).scaled(AutoStartIconSize * ratio, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        pixmap.setDevicePixelRatio(ratio);
    }
    painter->drawPixmap(iconRect, pixmap);

    // draw name
    QFont font = painter->font();
    font.setPixelSize(13);
    QFontMetrics fontMetrics(font);
    QRect nameRect = option.rect;
    nameRect.setLeft(iconRect.right() + 10);
    nameRect.setTop(rect.top() + 20);
    nameRect.setRight(option.rect.right() - 10);
    nameRect.setHeight(fontMetrics.height() * 1.2);
    painter->setFont(font);
    if (!name.isEmpty()) {
        painter->drawText(nameRect, name);
    }
    else {
        painter->drawText(nameRect, "Unknown");
    }

    // draw comment
    QFont font1 = painter->font();
    font1.setPixelSize(11);
    QFontMetrics fm(font1);
    QRect commentRect = option.rect;
    commentRect.setLeft(nameRect.left());
    commentRect.setRight(nameRect.right());
    commentRect.setTop(nameRect.bottom() + 10);
    commentRect.setBottom(option.rect.bottom() - 10);
    painter->setFont(font1);
    const QString &commentStr = fm.elidedText(comment.isEmpty() ? name : comment, Qt::ElideRight, commentRect.width());
    painter->drawText(commentRect, commentStr);
}

QWidget *AutoStartDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    QPushButton *removeBtn = new QPushButton(parent);
    removeBtn->setText("X");
    removeBtn->setStyleSheet("QPushButton{background-color: rgba(0, 0, 0, 0);}");
    connect(removeBtn, &QPushButton::clicked, this, &AutoStartDelegate::removeBtnClicked);

    return removeBtn;
}

void AutoStartDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)

    QPushButton *mEditor = static_cast<QPushButton *>(editor);
    mEditor->setFixedSize(mEditor->size() + QSize(10, 10));

    QRect rect = option.rect;
    editor->setGeometry(rect.x() + rect.width() - mEditor->width(), rect.y(), mEditor->width(), mEditor->height());
}
