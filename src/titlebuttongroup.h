#ifndef TITLEBUTTONGROUP_H
#define TITLEBUTTONGROUP_H

#include <QWidget>

class SystemButton;

class TitleButtonGroup : public QWidget
{
    Q_OBJECT
public:
    explicit TitleButtonGroup(QWidget *parent = 0);

    void updateMaxIcon(bool b);

signals:
    void showMenu();
    void showMax();
    void showMin();
    void requestQuit();

private:
    SystemButton *menu_btn;
    SystemButton *minimun_btn;
    SystemButton *maximum_btn;
    SystemButton *clost_btn;
};

#endif // TITLEBUTTONGROUP_H
