#include "abstrackplugin.h"

AbstrackPlugin::AbstrackPlugin(QWidget *parent)
    : QWidget{parent}
{

}

QIcon AbstrackPlugin::getPluginIcon() const
{
    return pluginIcon;
}

void AbstrackPlugin::setPluginIcon(const QIcon &newPluginIcon)
{
    pluginIcon = newPluginIcon;
}

QString AbstrackPlugin::getPluginName() const
{
    return pluginName;
}

void AbstrackPlugin::setPluginName(const QString &newPluginName)
{
    pluginName = newPluginName;
}
