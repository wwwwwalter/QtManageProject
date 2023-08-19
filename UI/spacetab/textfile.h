#ifndef TEXTFILE_H
#define TEXTFILE_H

#include <QWidget>

namespace Ui {
class TextFile;
}

class TextFile : public QWidget
{
    Q_OBJECT

public:
    explicit TextFile(QWidget *parent = nullptr);
    ~TextFile();

private:
    Ui::TextFile *ui;
};

#endif // TEXTFILE_H
