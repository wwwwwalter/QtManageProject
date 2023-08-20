#ifndef TEXTFILE_H
#define TEXTFILE_H

#include <QWidget>
#include "abstractfile.h"
#include <QFileInfo>
#include <QFile>

namespace Ui {
class TextFile;
}

class TextFile : public AbstractFile
{
    Q_OBJECT

public:
    explicit TextFile(QFileInfo fileInfo,QWidget *parent = nullptr);
    ~TextFile();

private:
    Ui::TextFile *ui;
    QFileInfo privateFileInfo;


    // AbstractFile interface
public:
    virtual void openFile(QFileInfo fileInfo);
    virtual void closeFile();
    virtual void saveFile();
    virtual void saveFileAs(QFileInfo destFileInfo);
};

#endif // TEXTFILE_H
