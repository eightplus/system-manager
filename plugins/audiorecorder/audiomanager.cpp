#include "audiomanager.h"
#include "audiowidget.h"
#include "resultwidget.h"

#include <QStackedLayout>

AudioManager::AudioManager(QObject *parent)
    : QObject(parent),
      m_frame(new QFrame)
{
    AudioWidget *audioWidget = new AudioWidget();
    ResultWidget *resultWidget = new ResultWidget();

    QStackedLayout *layout = new QStackedLayout;
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(audioWidget);
    layout->addWidget(resultWidget);

    m_frame->setLayout(layout);
    m_frame->setObjectName("AudioRecorderWidget");
    m_frame->setStyleSheet("#AudioRecorderWidget {"
                          "background-color: rgba(255, 255, 255, .03);"
                          "}");

    connect(audioWidget, &AudioWidget::requestFinish, this, [this, layout, resultWidget] () {
        layout->setCurrentWidget(resultWidget);
    });
    connect(resultWidget, &ResultWidget::cancelled, this, [=] () {
        layout->setCurrentWidget(audioWidget);
    });
}

void AudioManager::initialize()
{

}

QWidget *AudioManager::centralWidget()
{
    return m_frame;
}

const QString AudioManager::name() const
{
    return QStringLiteral("audio");
}
