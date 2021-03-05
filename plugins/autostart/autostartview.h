#ifndef AUTOSTARTVIEW_H
#define AUTOSTARTVIEW_H

#include <QListView>

class AutoStartView : public QListView
{
    Q_OBJECT

public:
    AutoStartView(QWidget *parent = nullptr);

    const QModelIndex &currentHoverIndex() const;

private slots:
    void listViewCurrentHoverChanged(const QModelIndex &previous, const QModelIndex &current);

protected:
    void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;

private:
    QModelIndex m_previousIndex;
    QModelIndex m_currentIndex;
};

#endif // AUTOSTARTVIEW_H
