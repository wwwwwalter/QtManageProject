#include "irregularer.h"

Irregularer::Irregularer(QWidget *parent)
    : QWidget{parent}
{
    vboxLayout = new QVBoxLayout;
    vboxLayout->setContentsMargins(0,0,0,0);
    setLayout(vboxLayout);



}

void Irregularer::addWidget(QWidget *widget)
{
    vboxLayout->addWidget(widget);
}

QVBoxLayout *Irregularer::getVBoxLayout()
{
    return vboxLayout;
}
