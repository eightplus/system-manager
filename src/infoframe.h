#ifndef INFOFRAME_H
#define INFOFRAME_H

#include <QFrame>
#include <QButtonGroup>

class QStackedWidget;
class QStackedLayout;
class QHBoxLayout;
class QVBoxLayout;
class QPushButton;

class InfoFrame : public QFrame
{
    Q_OBJECT
public:
    explicit InfoFrame(QWidget *parent = 0);
    ~InfoFrame();

    void initUI();
    void initLeftContent();
    void initRightContent();
    void refreshWidgets(const QStringList &types);

public slots:
    void setNavgationEnabled(const bool enabled);
    void onNavButtonClicked(const int index);

private:
    QHBoxLayout *m_layout;
    QVBoxLayout *m_lLayout;
    QVBoxLayout *m_rLayout;
    QStackedLayout *m_stackedLayout;
    QStackedWidget *m_stackWidget;
    QButtonGroup *m_navButtonsGroup = nullptr;
    int m_index;
};

#endif // INFOFRAME_H
