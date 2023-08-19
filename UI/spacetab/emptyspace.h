#ifndef EMPTYSPACE_H
#define EMPTYSPACE_H

#include <QWidget>

namespace Ui {
class EmptySpace;
}

class EmptySpace : public QWidget
{
    Q_OBJECT

public:
    explicit EmptySpace(QWidget *parent = nullptr);
    ~EmptySpace();

private:
    Ui::EmptySpace *ui;
};

#endif // EMPTYSPACE_H
