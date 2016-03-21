#include "qgraphicsclickablerectitem.h"
#include "mainwindow.h"
#include <QDebug>
#include <QApplication>


void QGraphicsClickableRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    //MainWindow::getMainWindow()->squareTurnOff(number);
   // MainWindow::getMainWindow()->redraw();
    QWidgetList widgets = qApp->topLevelWidgets();
       for (QWidgetList::iterator i = widgets.begin(); i != widgets.end(); ++i)
          if ((*i)->objectName() == "MainWindow")
              ((MainWindow*) (*i))->squareTurnOff(number);
}
