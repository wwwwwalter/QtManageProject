#ifndef ABSTRACTFILE_H
#define ABSTRACTFILE_H

#include <QWidget>
#include <QFileInfo>

class AbstractFile : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractFile(QWidget *parent = nullptr);

public:
    virtual void openFile(QFileInfo fileInfo) = 0;
    virtual void closeFile() = 0;
    virtual void saveFile() = 0;
    virtual void saveFileAs(QFileInfo destFileInfo) = 0;

signals:

};

#endif // ABSTRACTFILE_H
