#ifndef GRIDTABLEVIEW_H
#define GRIDTABLEVIEW_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>

class GridTableView : public QTableView
{
    Q_OBJECT
public:
    explicit GridTableView(QWidget *parent = nullptr);


public:
    QStandardItemModel *model;


private:
    int beginColNum,endColNum;
    int beginRowNum,endRowNum;
public:
    int selectedColNum;
    int selectedRowNum;

    // QWidget interface
protected:
    virtual void mouseReleaseEvent(QMouseEvent *event);

};

#endif // GRIDTABLEVIEW_H
