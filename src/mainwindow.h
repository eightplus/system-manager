#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

class InfoFrame;
class MonitorFrame;
class CleanFrame;
class ToolsFrame;
class HomeWidget;
class TopToolBar;
class ExtensionEdgeWidget;
class RightPanel;

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget *parent=0);
    ~MainWindow();

    void slideToHomePage();
    void slideToSubWidgets();
    void initEdgeWidget();
    void setEdgeWidgetVisible(bool visible, bool immediately);
    void setRightPanelVisible(bool visible);

public slots:
    void moveCenter();
    void toggleRightPanel();
    void onHideRightPanel();

protected:
    virtual void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    virtual void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;

private:
    QWidget *centralWidget;
    TopToolBar *m_titlebar;
    QWidget *m_currentWidget;
    HomeWidget *m_homeWidget;
    QStackedWidget  *m_subStacksWidget;
    InfoFrame *m_infoWidget;
    MonitorFrame *m_monitorWidget;
    CleanFrame *m_cleanWidget;
    ToolsFrame *m_toolsWidget;
    ExtensionEdgeWidget *m_edgeWidget = nullptr;
    bool m_edgeShowed;
    RightPanel *m_rightPanel;
    QPoint m_movePoint;
    QPoint m_endPoint;
    bool m_mousePress;
};

#endif // MAINWINDOW_H
