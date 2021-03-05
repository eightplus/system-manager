#include "videomanager.h"
#include "videowidget.h"

VideoManager::VideoManager(QObject *parent)
    : QObject(parent)
{

}

void VideoManager::initialize()
{
    m_videoWidget = new VideoWidget;
}

QWidget *VideoManager::centralWidget()
{
    return m_videoWidget;
}

const QString VideoManager::name() const
{
    return QStringLiteral("video");
}
