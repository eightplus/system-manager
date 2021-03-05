#ifndef TOOLSFRAME_H
#define TOOLSFRAME_H

#include <QFrame>
#include <QButtonGroup>

#include "tools/pluginloader.h"

class QStackedLayout;
class QHBoxLayout;
class QVBoxLayout;

class ToolsFrame : public QFrame
{
    Q_OBJECT
public:
    explicit ToolsFrame(QWidget *parent = 0);
    ~ToolsFrame();

    void initUI();
    void initLeftContent();
    void initRightContent();

public slots:
    void setNavgationEnabled(const bool enabled);
    void onNavButtonClicked(int index);
    void pluginAdded(QWidget * const w, const QString &name);

private:
    QHBoxLayout *m_layout;
    QVBoxLayout *m_lLayout;
    QVBoxLayout *m_rLayout;
    QStackedLayout *m_stackedLayout;
    QButtonGroup *m_navButtonsGroup = nullptr;
    int m_currentIndex;
    PluginLoader *m_pluginLoader;
};

#endif // TOOLSFRAME_H
