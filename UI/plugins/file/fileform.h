#ifndef FILEFORM_H
#define FILEFORM_H

#include <QDir>
#include <QWidget>

namespace Ui {
class FileForm;
}

class FileForm : public QWidget
{
    Q_OBJECT

public:
    explicit FileForm(QWidget *parent = nullptr);
    ~FileForm();

private:
    Ui::FileForm *ui;

    QString projectName;
    QDir workPath;
    QStringList templeteList;
};

#endif // FILEFORM_H
