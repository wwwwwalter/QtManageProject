#ifndef NEWFILEDIALOG_H
#define NEWFILEDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include <QListView>

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
};

#endif // NEWFILEDIALOG_H
