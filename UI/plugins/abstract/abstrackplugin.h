#ifndef ABSTRACKPLUGIN_H
#define ABSTRACKPLUGIN_H

#include <QIcon>
#include <QWidget>


class AbstrackPlugin : public QWidget
{
    Q_OBJECT
public:
    explicit AbstrackPlugin(QWidget *parent = nullptr);

private:
    QIcon pluginIcon;
    QString pluginName;

public:
    QIcon getPluginIcon() const;
    void setPluginIcon(const QIcon &newPluginIcon);
    QString getPluginName() const;
    void setPluginName(const QString &newPluginName);

public:
    virtual void doCreateProject() = 0;

signals:

};

#endif // ABSTRACKPLUGIN_H
