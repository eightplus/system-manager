#ifndef TOPTOOLBAR_H
#define TOPTOOLBAR_H

#include <QWidget>
#include <QPixmap>

class QStackedWidget;
class QMenu;
class QVBoxLayout;
class QHBoxLayout;
class TitleButtonGroup;

class TopToolBar : public QWidget
{
    Q_OBJECT
public:
    explicit TopToolBar(QWidget *parent = 0);
    ~TopToolBar();

    void setMiddleWidget(QWidget *w);
    void updateMaxButtonStatus(bool b);

public slots:
    void setBackBtnVisible();

signals:
    void requestUpdateMaxBtn();
    void requestShowHomePage();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void onAbout();
    void onHelp();
    void onSetting();

private:
    void initUI();
    void initTopTitleWidget();
    void initLeftContent();
    void initMiddleContent();
    void initRightContent();
    void initMenu();

private:
    QStackedWidget *m_titleStacked;
    QHBoxLayout *m_layout;
    QHBoxLayout *m_mLayout;
    QMenu *m_menu;
    TitleButtonGroup *buttonGroup;
};

#endif // TOPTOOLBAR_H
