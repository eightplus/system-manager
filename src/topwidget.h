#ifndef TOPWIDGET_H
#define TOPWIDGET_H

#include <QWidget>
#include <QPixmap>

class QStackedWidget;
class QVBoxLayout;
class ReadmeWidget;
class AuthorWidget;
class TopToolBar;

class TopWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TopWidget(QWidget *parent = 0);
    ~TopWidget();

public slots:
    void displayDefaultPage();

signals:
    void requestBack();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    void initUI();
    void initReadmeWidget();

private:
    AuthorWidget *m_authorWidget;
    ReadmeWidget *m_readmeWidget;
    QVBoxLayout *m_layout;
};

#endif // TOPWIDGET_H
