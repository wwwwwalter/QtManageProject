#ifndef SPACEWIDGETGRIDDESIGNDIALOG_H
#define SPACEWIDGETGRIDDESIGNDIALOG_H

#include <QDialog>
#include <QItemSelectionModel>
#include <QStandardItemModel>
#include <QItemSelectionRange>

namespace Ui {
class SpaceWidgetGridDesignDialog;
}

class SpaceWidgetGridDesignDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SpaceWidgetGridDesignDialog(QWidget *parent = nullptr);
    ~SpaceWidgetGridDesignDialog();

private:
    Ui::SpaceWidgetGridDesignDialog *ui;


    QStandardItemModel *model;
    QItemSelectionModel *selectionModel;
    QItemSelectionRange *selectionRange;
};

#endif // SPACEWIDGETGRIDDESIGNDIALOG_H
