#ifndef AUDIOFORM_H
#define AUDIOFORM_H

#include <QDir>
#include <QWidget>
#include "../abstract/abstrackplugin.h"

namespace Ui {
class AudioForm;
}

class AudioForm : public AbstrackPlugin
{
    Q_OBJECT

public:
    explicit AudioForm(QWidget *parent = nullptr);
    ~AudioForm();

private:
    Ui::AudioForm *ui;

private:
    QString projectName;
    QDir workDir;
    QStringList templeteList;

public:
    void doCreate();


    // AbstrackPlugin interface
public:
    virtual QDir doCreateProject();

};

#endif // AUDIOFORM_H
