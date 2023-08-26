#ifndef GRIDER_H
#define GRIDER_H

#include <QGridLayout>
#include <QWidget>


class Grider : public QWidget
{
    Q_OBJECT
public:
    explicit Grider(QWidget *parent = nullptr);


private:
    QGridLayout *gridLayout;

public:
    void addWidget(int rols,int cols);
    void addWidget(QWidget *widget,int rols,int cols);
    QGridLayout *getGridLayout();
    int indexOf(QWidget *widget);

signals:

};

#endif // GRIDER_H
