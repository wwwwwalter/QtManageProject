#ifndef VIDEOSPACE_H
#define VIDEOSPACE_H

#include <QWidget>

namespace Ui {
class VideoSpace;
}

class VideoSpace : public QWidget
{
    Q_OBJECT

public:
    explicit VideoSpace(QWidget *parent = nullptr);
    ~VideoSpace();

private:
    Ui::VideoSpace *ui;
};

#endif // VIDEOSPACE_H
