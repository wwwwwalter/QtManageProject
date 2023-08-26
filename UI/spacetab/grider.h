#ifndef GRIDER_H
#define GRIDER_H

#include <QGridLayout>
#include <QWidget>


class Grider : public QWidget
{
    Q_OBJECT
public:
    explicit Grider(QWidget *parent = nullptr);

    QAction *insertGridLayoutAction;

private slots:
    void slotInsertGridLayout();



private:
    QGridLayout *gridLayout;
    QPoint point;

public:
    void addWidget(int rols,int cols);
    void addWidget(QWidget *widget,int rols,int cols);
    QGridLayout *getGridLayout();
    int indexOf(QWidget *widget);

signals:


    // QWidget interface
protected:
    virtual void contextMenuEvent(QContextMenuEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
};

#endif // GRIDER_H
