#include "gridtableview.h"
#include <QHeaderView>

GridTableView::GridTableView(QWidget *parent)
    : QTableView{parent}
{
    model = new QStandardItemModel;

    model->setRowCount(10);
    model->setColumnCount(10);
    setModel(model);
    horizontalHeader()->setDefaultSectionSize(50);
    verticalHeader()->setDefaultSectionSize(50);
    setGridStyle(Qt::DotLine);
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    QPalette palette;
    palette.setColor(QPalette::Highlight,QColor(38, 165, 38,255));
    setPalette(palette);



    selectedColNum = 0;
    selectedRowNum = 0;



    connect(this,&GridTableView::pressed,this,[=](const QModelIndex &index){
        beginColNum = index.column();
        beginRowNum = index.row();
    });
}

void GridTableView::mouseReleaseEvent(QMouseEvent *event)
{
    endColNum = currentIndex().column();
    endRowNum = currentIndex().row();

    selectedColNum = abs(endColNum-beginColNum)+1;
    selectedRowNum = abs(endRowNum-beginRowNum)+1;
    QAbstractItemView::mouseReleaseEvent(event);
}
