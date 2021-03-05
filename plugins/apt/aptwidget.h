#ifndef APTWIDGET_H
#define APTWIDGET_H

#include <QWidget>
#include <QButtonGroup>

class QPushButton;
class SelectFileFrame;
class InstallFrame;
class UnInstallFrame;
class QStackedLayout;
class QHBoxLayout;
class QVBoxLayout;

class AptWidget : public QWidget
{
    Q_OBJECT

public:
    enum PageType
    {
        SelectFilePage,
        InstallPage,
        UnInstallPage,
        Invalid,
    };

    explicit AptWidget(QWidget* parent = 0);
    ~AptWidget();

    void initUI();
    void initLeftContent();
    void initRightContent();
    void showSelectFilePage();
    void showInstallPage();
    void showUninstallPage();

public slots:
    void setNavgationEnabled(const bool enabled);
    void onNavButtonClicked(PageType index);

private:
//    QPushButton *m_okBtn;
    PageType m_pageType;
    SelectFileFrame *m_selectFileFrame;
    InstallFrame *m_installFrame;
    UnInstallFrame *m_uninstallFrame;
    QHBoxLayout *m_layout;
    QVBoxLayout *m_lLayout;
    QVBoxLayout *m_rLayout;
    QStackedLayout *m_stackedLayout;
    QButtonGroup *m_navButtonsGroup = nullptr;

};

#endif // APTWIDGET_H
