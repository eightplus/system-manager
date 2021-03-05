#ifndef UNINSTALLFRAME_H
#define UNINSTALLFRAME_H

#include <QFrame>

class QVBoxLayout;

class UnInstallFrame : public QFrame
{
    Q_OBJECT
public:
    explicit UnInstallFrame(QWidget *parent = 0);

private:
    void initContent();

private:
    QVBoxLayout *m_layout;
};

#endif // UNINSTALLFRAME_H
