#ifndef QGRAPHICSCLICKABLERECTITEM_H
#define QGRAPHICSCLICKABLERECTITEM_H
#include <QGraphicsRectItem>
class MainWindow;

class QGraphicsClickableRectItem : public QGraphicsRectItem
{
public:
    QGraphicsClickableRectItem(qreal x, qreal y, qreal w, qreal h,int n, MainWindow& main): QGraphicsRectItem(x,y,w,h),number(n), main(main){}

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    int number;
    MainWindow& main;
};

#endif // QGRAPHICSCLICKABLERECTITEM_H
