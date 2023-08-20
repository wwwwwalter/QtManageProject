#ifndef PLAYLISTFILE_H
#define PLAYLISTFILE_H

#include <QWidget>

namespace Ui {
class PlayListFile;
}

class PlayListFile : public QWidget
{
    Q_OBJECT

public:
    explicit PlayListFile(QWidget *parent = nullptr);
    ~PlayListFile();

private:
    Ui::PlayListFile *ui;
};

#endif // PLAYLISTFILE_H
