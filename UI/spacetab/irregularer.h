#ifndef IRREGULARER_H
#define IRREGULARER_H

#include <QVBoxLayout>
#include <QWidget>


class Irregularer : public QWidget
{
    Q_OBJECT
public:
    explicit Irregularer(QWidget *parent = nullptr);

private:
    QVBoxLayout *vboxLayout;

public:
    void addWidget(QWidget *widget);
    QVBoxLayout *getVBoxLayout();


};

#endif // IRREGULARER_H
