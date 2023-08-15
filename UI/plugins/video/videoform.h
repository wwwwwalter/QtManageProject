#ifndef VIDEOFORM_H
#define VIDEOFORM_H

#include <QDir>
#include <QWidget>

namespace Ui {
class VideoForm;
}

class VideoForm : public QWidget
{
    Q_OBJECT

public:
    explicit VideoForm(QWidget *parent = nullptr);
    ~VideoForm();

private:
    Ui::VideoForm *ui;

    QString projectName;
    QDir workPath;
    QStringList templeteList;
};

#endif // VIDEOFORM_H
