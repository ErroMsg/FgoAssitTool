#include "fgographicsview.h"
#include "mainwindow.h"
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QDebug>

FgoGraphicsView::FgoGraphicsView(QWidget *parent)
{
    setMouseTracking(true);
}

void FgoGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QPoint viewPoint = event->pos();
    QPointF scenePoint = mapToScene(viewPoint);

    QString strCoord = QString("ViewPos:(%1,%2),ScenePos:(%3,%4)")
                            .arg(viewPoint.x()).arg(viewPoint.y())
                            .arg(scenePoint.x()).arg(scenePoint.y());

    QGraphicsItem *pItem = scene()->itemAt(scenePoint,QTransform());
    if(pItem)
    {
        //qDebug()<<pPosItem;
        QPointF posItem = pItem->mapFromScene(scenePoint);
        QString strItemPos = QString("ItemPos:(%1,%2)").arg(posItem.x()).arg(posItem.y());
        strCoord += strItemPos;
    }

    emit Signal_UpdateCoor(strCoord);

    QGraphicsView::mouseMoveEvent(event);
}

void FgoGraphicsView::wheelEvent(QWheelEvent *event)
{
    QGraphicsView::wheelEvent(event);
}
