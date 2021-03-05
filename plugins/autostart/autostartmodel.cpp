#include "autostartmodel.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QSize>
#include <QDebug>

AutoStartModel::AutoStartModel(QObject *parent) : QAbstractListModel(parent)
    , m_removeIndex(QModelIndex())
    , m_hoverIndex(QModelIndex())
    , m_currentXOffset(0)
    , m_maxXOffset(0)
    , m_timerId(0)
    , m_clearAll(false)
{
    //TODO: test code
    QString jsonContent("{"
            "\"items\" : ["
            "{\"exec\": \"smplayer\", \"name\": \"SMPlayer\", \"comment\": \"aaaaaaaa\", \"icon\": \":/images/icon.png\"},"
            "{\"exec\": \"mpv\", \"name\": \"MPV\", \"comment\": \"bbbbbbbbbb\", \"icon\": \":/images/icon.png\"},"
            "{\"exec\": \"qtav\", \"name\": \"QtAV\", \"comment\": \"bbbbbbbbbb\", \"icon\": \":/images/icon.png\"},"
            "{\"exec\": \"d-feet\", \"name\": \"d-feet\", \"comment\": \"cccccccccc\", \"icon\": \":/images/icon.png\"},"
            "{\"exec\": \"yelp\", \"name\": \"yelp\", \"comment\": \"dddddddddddd\", \"icon\": \":/images/icon.png\"},"
            "{\"exec\": \"gedit\", \"name\": \"gedit\", \"comment\": \"eeeeeeee\", \"icon\": \":/images/icon.png\"}"
            "]"
            "}");

    QJsonParseError jsonError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonContent.toUtf8(), &jsonError);
    if (!jsonDocument.isNull() && (jsonError.error == QJsonParseError::NoError)) {
        const auto &obj = jsonDocument.object();

        beginResetModel();
        m_jsonArray = obj.value("items").toArray();//m_jsonArray = jsonDocument.array();
        endResetModel();
        if (m_jsonArray.isEmpty()) {
            emit modelStateChanged(true);
        }

        for (auto jsonObj : m_jsonArray) {
            auto obj = jsonObj.toObject();
            qDebug() << obj.value("exec").toString();
            qDebug() << obj.value("name").toString();
            qDebug() << obj.value("comment").toString();
        }
    }
    else {
        emit modelStateChanged(true);
    }


    QString str("{"
            "\"exec\": \"video-player\", \"name\": \"Video Player\", \"comment\": \"test test test\", \"icon\": \":/images/icon.png\""
            "}");
    this->addSingleItem(str);
}

int AutoStartModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_jsonArray.size();
}

QVariant AutoStartModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() && m_jsonArray.size() <= 0 && index.row() > m_jsonArray.size()) {
        return QVariant();
    }

    QJsonObject obj = m_jsonArray.at(m_jsonArray.size() - 1 - index.row()).toObject();

    switch (role) {
    case AutoStartExecRole:
        return obj.value("id").toString();
    case AutoStartNameRole:
        return obj.value("name").toString();
    case AutoStartCommentRole:
        return obj.value("comment").toString();
    case AutoStartIconRole:
        return obj.value("icon").toString();
    case Qt::SizeHintRole:
        return QSize(0, 88);
    case AutoStartRemoveRole: {
        if (m_clearAll || m_removeIndex == index) {
            return true;
        }
        return false;
    }
    case AutoStartXOffsetRole:
        return m_currentXOffset;
    case AutoStartHoverRole:
        return m_hoverIndex == index;
    default:
        break;
    }

    return QVariant();
}

Qt::ItemFlags AutoStartModel::flags(const QModelIndex &index) const
{
    if (index.isValid()) {
        return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
    }

    return QAbstractListModel::flags(index);
}

void AutoStartModel::clearAllAutostartItems()
{
    beginResetModel();
    m_jsonArray = {};
    endResetModel();

    emit modelStateChanged(true);
}

void AutoStartModel::addSingleItem(const QString &str)
{
    if (m_jsonArray.isEmpty()) {
        emit modelStateChanged(false);
    }
    else {
        m_jsonArray.append(QJsonDocument::fromJson(str.toLocal8Bit().data()).object());
        const QModelIndex mindex = index(0);
        emit dataChanged(mindex, mindex);
    }
}

void AutoStartModel::showAnimationToClearAllItmes(int maxXOffset)
{
    m_clearAll = true;//只有当点击清空全部按钮时，才置为true
    m_maxXOffset = maxXOffset;

    if (m_timerId == 0) {
        m_timerId = startTimer(10);
    }
}

void AutoStartModel::showAnimationToRemoveSingleItem(const QModelIndex &removeIndex, int maxXOffset)
{
    m_removeIndex = removeIndex;
    m_maxXOffset = maxXOffset;

    if (m_timerId == 0) {
        m_timerId = startTimer(10);
    }
}

void AutoStartModel::setHoverIndex(const QModelIndex &index)
{
    m_hoverIndex = index;
    emit dataChanged(m_hoverIndex, m_hoverIndex);
}

void AutoStartModel::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)

    if (m_currentXOffset < m_maxXOffset) {
        m_currentXOffset += 30;
        if (m_clearAll) {
            emit layoutChanged();
        } else {
            emit dataChanged(m_removeIndex, m_removeIndex);
        }
        return;
    }

    if (m_timerId != 0) {
        killTimer(m_timerId);
    }

    if (m_clearAll) {
        emit removeAllAnimationFinished();
    }
    else {
        emit removeSingleAnimationFinished(m_removeIndex);
    }

    m_removeIndex = QModelIndex();
    m_currentXOffset = 0;
    m_timerId = 0;
    m_clearAll = false;
}

void AutoStartModel::removeSingleItem(const QModelIndex &index)
{
    QJsonObject obj = m_jsonArray.at(m_jsonArray.size() - 1 - index.row()).toObject();

    //TODO: remove data from backend
    qDebug() << "removeSingleItem exec: " << obj.value("exec").toString();

    m_jsonArray.removeAt(m_jsonArray.size() - 1 - index.row());
    emit dataChanged(index, index);

    if (m_jsonArray.size() == 0) {
        emit modelStateChanged(true);
    }
}
