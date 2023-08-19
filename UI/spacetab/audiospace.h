#ifndef AUDIOSPACE_H
#define AUDIOSPACE_H

#include <QWidget>

namespace Ui {
class AudioSpace;
}

class AudioSpace : public QWidget
{
    Q_OBJECT

public:
    explicit AudioSpace(QWidget *parent = nullptr);
    ~AudioSpace();

private:
    Ui::AudioSpace *ui;
};

#endif // AUDIOSPACE_H
