#ifndef TITLEHEADER_H
#define TITLEHEADER_H

#include <QWidget>

class TitleHeader : public QWidget
{
    Q_OBJECT
public:
    explicit TitleHeader(const QString &title, QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *e) Q_DECL_OVERRIDE;

private:
    QString m_title;
};

#endif // TITLEHEADER_H
