#ifndef NEWFILEDIALOG_H
#define NEWFILEDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QListView>
#include <QFileinfo>
#include <QDir>

namespace Ui {
class NewFileDialog;
}

class NewFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewFileDialog(QWidget *parent = nullptr);
    ~NewFileDialog();

private:
    Ui::NewFileDialog *ui;

    QStandardItemModel *model;

    QString extensionName;
    QString fileName;
    QString savePath;
    QFileInfo fileInfo;
    QDir fileDir;

signals:
    void fileCreateComplete(QFileInfo newFileInfo);

};

#endif // NEWFILEDIALOG_H
