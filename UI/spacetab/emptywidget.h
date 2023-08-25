#ifndef EMPTYWIDGET_H
#define EMPTYWIDGET_H

#include <QWidget>

class EmptyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EmptyWidget(QWidget *parent = nullptr);





    QAction *insertGridLayoutAction;
    QAction *insertHorizontalSplitterAction;
    QAction *insertVerticalSplitterAction;
    QAction *openFileAction;

    QAction *insertWidgetOnTheLeftAction;
    QAction *insertWidgetOnTheRightAction;
    QAction *insertWidgetOnTheTopAction;
    QAction *insertWidgetOnTheBottomAction;
    QAction *deleteThisWidgetAction;

  private slots:
    void slotInsertGridLayout();
    void slotInsertHorizontalSplitter();
    void slotInsertVerticalSplitter();

    void slotInsertWidgetOnTheLeft();
    void slotInsertWidgetOnTheRight();
    void slotInsertWidgetOnTheTop();
    void slotInsertWidgetOnTheBottom();
    void slotDeleteThisWidgetAction();


    // QWidget interface
protected:
    virtual void contextMenuEvent(QContextMenuEvent *event);
};

#endif // EMPTYWIDGET_H
