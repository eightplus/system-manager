#ifndef AUTOSTARTMODEL_H
#define AUTOSTARTMODEL_H

#include <QAbstractListModel>
#include <QJsonArray>

class AutoStartModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum AutoStartDataRole {
        AutoStartExecRole = Qt::UserRole + 1,
        AutoStartNameRole = Qt::UserRole + 2,
        AutoStartCommentRole = Qt::UserRole + 3,
        AutoStartIconRole = Qt::UserRole + 4,
        AutoStartRemoveRole = Qt::UserRole + 5,
        AutoStartXOffsetRole = Qt::UserRole + 6,
        AutoStartHoverRole = Qt::UserRole + 7
    };

    AutoStartModel(QObject *parent = nullptr);

public:
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

public slots:
    void clearAllAutostartItems();
    void removeSingleItem(const QModelIndex &index);
    void showAnimationToClearAllItmes(int maxXOffset);
    void showAnimationToRemoveSingleItem(const QModelIndex &removeIndex, int maxXOffset);
    void setHoverIndex(const QModelIndex &index);

signals:
    void removeSingleAnimationFinished(const QModelIndex &index);
    void removeAllAnimationFinished();
    void modelStateChanged(bool clear);

protected:
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;

private slots:
    void addSingleItem(const QString &str);

private:
    QJsonArray m_jsonArray;
    QModelIndex m_removeIndex;
    QModelIndex m_hoverIndex;

    int m_currentXOffset;
    int m_maxXOffset;
    int m_timerId;
    bool m_clearAll;
};

#endif // AUTOSTARTMODEL_H
