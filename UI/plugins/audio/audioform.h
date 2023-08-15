#ifndef AUDIOFORM_H
#define AUDIOFORM_H

#include <QWidget>
#include <QDir>

namespace Ui {
class AudioForm;
}

class AudioForm : public QWidget
{
    Q_OBJECT

public:
    explicit AudioForm(QWidget *parent = nullptr);
    ~AudioForm();

private:
    Ui::AudioForm *ui;

private:
    QString projectName;
    QDir workPath;
    QStringList templeteList;

};

#endif // AUDIOFORM_H
