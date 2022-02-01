#include "qgraphicsclickablerectitem.h"
#include "mainwindow.h"
#include <QDebug>
#include <QApplication>


void QGraphicsClickableRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    main.squareTurnOff(number);
}
