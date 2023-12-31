#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>
#include <QDir>
#include <QItemSelectionModel>
#include <QStandardItemModel>
#include "../plugins/file/fileform.h"
#include "../plugins/video/videoform.h"
#include "../plugins/audio/audioform.h"

namespace Ui {
class NewProjectDialog;
}

class NewProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewProjectDialog(QWidget *parent = nullptr);
    ~NewProjectDialog();

private:
    Ui::NewProjectDialog *ui;


    //project info
private:
    QDir projectDir;
public:
    QDir getProjectDir();



    //plugins
private:
    FileForm *fileForm;
    VideoForm *videoForm;
    AudioForm *audioForm;

private:
    QStandardItemModel *model;
    QItemSelectionModel *itemSelectionModel;


signals:
    void projectCreateComplete(QFileInfo projectConfigFileInfo);




};

#endif // NEWPROJECTDIALOG_H
