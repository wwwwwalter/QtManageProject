#ifndef FILEFORM_H
#define FILEFORM_H

#include <QDir>
#include <QWidget>
#include "../abstract/abstrackplugin.h"

namespace Ui {
class FileForm;
}

class FileForm : public AbstrackPlugin
{
    Q_OBJECT

public:
    explicit FileForm(QWidget *parent = nullptr);
    ~FileForm();

private:
    Ui::FileForm *ui;

    QString projectName;
    QDir workDir;
    QStringList templeteList;

    // AbstrackPlugin interface
public:
    virtual QDir doCreateProject();
};

#endif // FILEFORM_H
