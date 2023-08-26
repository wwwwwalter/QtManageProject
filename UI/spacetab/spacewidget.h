#ifndef SPACEWIDGET_H
#define SPACEWIDGET_H

#include <QWidget>

class SpaceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SpaceWidget(QWidget *parent = nullptr);






    QAction *openFileAction;
    QAction *insertGridLayoutAction;
    QAction *insertWidgetOnTheLeftAction;
    QAction *insertWidgetOnTheRightAction;
    QAction *insertWidgetOnTheTopAction;
    QAction *insertWidgetOnTheBottomAction;
    QAction *deleteThisWidgetAction;

  private slots:
    void slotOpenFile();
    void slotInsertGridLayout();
    void slotInsertWidgetOnTheLeft();
    void slotInsertWidgetOnTheRight();
    void slotInsertWidgetOnTheTop();
    void slotInsertWidgetOnTheBottom();
    void slotDeleteThisWidgetAction();


    // QWidget interface
protected:
    virtual void contextMenuEvent(QContextMenuEvent *event);

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event);
//    virtual void focusInEvent(QFocusEvent *event);
//    virtual void focusOutEvent(QFocusEvent *event);
};

#endif // SPACEWIDGET_H
