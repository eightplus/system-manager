#ifndef READMEWIDGET_H
#define READMEWIDGET_H

#include <QFrame>

class QLabel;
class QPushButton;

class ReadmeWidget : public QFrame
{
    Q_OBJECT
public:
    explicit ReadmeWidget(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;

signals:
    void requestShowBackBtn();

private:
    QLabel *m_label = nullptr;
    QPushButton *m_btn = nullptr;
};

#endif // READMEWIDGET_H
