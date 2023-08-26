#include "grider.h"
#include "spacewidget.h"

Grider::Grider(QWidget *parent)
    : QWidget{parent}
{
    gridLayout = new QGridLayout;
    setLayout(gridLayout);
    gridLayout->setSpacing(10);
    gridLayout->setContentsMargins(0,0,0,0);

    setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window,QColor(0,0,255));
    setPalette(palette);


}

void Grider::addWidget(int rols, int cols)
{
    for (int i = 0; i < rols; ++i) {
        gridLayout->setRowMinimumHeight(i,150);
        for (int j = 0; j < cols; ++j) {
            gridLayout->setColumnMinimumWidth(j,200);
            SpaceWidget *spaceWidget = new SpaceWidget;
            gridLayout->addWidget(spaceWidget,i,j);
        }
    }
}

void Grider::addWidget(QWidget *widget, int rols, int cols)
{
    for (int i = 0; i < rols; ++i) {
        gridLayout->setRowMinimumHeight(i,150);
        for (int j = 0; j < cols; ++j) {
            gridLayout->setColumnMinimumWidth(j,200);
            if(i==0&&j==0){
                gridLayout->addWidget(widget,i,j);
            }
            else{
                SpaceWidget *spaceWidget = new SpaceWidget;
                gridLayout->addWidget(spaceWidget,i,j);
            }

        }
    }
}

QGridLayout *Grider::getGridLayout()
{
    return static_cast<QGridLayout *>(this->layout());
}

int Grider::indexOf(QWidget *widget)
{
    return gridLayout->indexOf(widget);
}
