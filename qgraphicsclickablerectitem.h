#ifndef QGRAPHICSCLICKABLERECTITEM_H
#define QGRAPHICSCLICKABLERECTITEM_H
#include <QGraphicsRectItem>

class QGraphicsClickableRectItem : public QGraphicsRectItem
{
public:
    QGraphicsClickableRectItem(qreal x, qreal y, qreal w, qreal h,int n): QGraphicsRectItem(x,y,w,h),number(n){}

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    int number;
};

#endif // QGRAPHICSCLICKABLERECTITEM_H
