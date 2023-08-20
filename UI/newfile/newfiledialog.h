#ifndef NEWFILEDIALOG_H
#define NEWFILEDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QListView>
#include <QFileinfo>
#include <QDir>
#include <QIcon>

namespace Ui {
class NewFileDialog;
}

class NewFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewFileDialog(QDir saveDir, QWidget *parent = nullptr);
    ~NewFileDialog();

private:
    Ui::NewFileDialog *ui;

    QIcon emptyFileIcon;
    QIcon videoSpaceIcon;
    QIcon audioSpaceIcon;
    QIcon playListIcon;



    QStandardItemModel *model;
    QItemSelectionModel *selectionModel;

    QString suffix;
    QString fileName;
    QString savePath;
    QFileInfo fileInfo;
    QDir fileDir;

signals:
    void fileCreateComplete(QFileInfo newFileInfo);

};

#endif // NEWFILEDIALOG_H
