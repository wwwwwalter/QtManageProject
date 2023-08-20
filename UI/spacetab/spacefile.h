#ifndef SPACEFILE_H
#define SPACEFILE_H

#include <QWidget>

namespace Ui {
class SpaceFile;
}

class SpaceFile : public QWidget
{
    Q_OBJECT

public:
    explicit SpaceFile(QWidget *parent = nullptr);
    ~SpaceFile();

private:
    Ui::SpaceFile *ui;
};

#endif // SPACEFILE_H
