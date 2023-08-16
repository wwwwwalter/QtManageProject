#ifndef VIDEOFORM_H
#define VIDEOFORM_H

#include <QDir>
#include <QWidget>
#include "../abstract/abstrackplugin.h"

namespace Ui {
class VideoForm;
}

class VideoForm : public AbstrackPlugin
{
    Q_OBJECT

public:
    explicit VideoForm(QWidget *parent = nullptr);
    ~VideoForm();

private:
    Ui::VideoForm *ui;

    QString projectName;
    QDir workDir;
    QStringList templeteList;



    // AbstrackPlugin interface
public:
    virtual QDir doCreateProject();
};

#endif // VIDEOFORM_H
