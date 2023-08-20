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
    virtual void closeFile(QFileInfo fileInfo) = 0;
    virtual void saveFile(QFileInfo fileInfo) = 0;
    virtual void saveFileAs(QFileInfo sourceFileInfo,QFileInfo destFileInfo) = 0;

signals:

};

#endif // ABSTRACTFILE_H
