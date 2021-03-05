#ifndef AUTHORWIDGET_H
#define AUTHORWIDGET_H

#include <QFrame>

class QLabel;

class AuthorWidget : public QFrame
{
    Q_OBJECT
public:
    explicit AuthorWidget(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;

private:
    QLabel *m_label = nullptr;
};

#endif // AUTHORWIDGET_H
