#ifndef REMOVEFILEDIALOG_H
#define REMOVEFILEDIALOG_H

#include <QDialog>
#include <QFileInfo>

namespace Ui {
class RemoveFileDialog;
}

class RemoveFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveFileDialog(const QFileInfo &fileInfo, QWidget *parent = nullptr);
    ~RemoveFileDialog();

private:
    Ui::RemoveFileDialog *ui;

signals:
    void removePermanently(bool permanently);


};

#endif // REMOVEFILEDIALOG_H
