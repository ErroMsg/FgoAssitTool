#include "fgoresultdisplayer.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPen>
#include <QBrush>

FgoResultDisplayer::FgoResultDisplayer(QString strTitle, QWidget *parent)
    : FgoDisplayerWidget(strTitle,parent)
{
}

void FgoResultDisplayer::postMatResult(QPoint pt, int width, int height)
{
    if(!m_pPostedImage)
        return;
    QRect rc(0,0,width,height);
    QPointF pointLoc = m_pPostedImage->mapToScene(pt);
    QGraphicsRectItem *pRectItem = new QGraphicsRectItem(rc);
    QPen pen(QColor(0,0,255),4);
    QBrush brush(QColor(0,0,255,100));
    pRectItem->setPen(pen);
    pRectItem->setBrush(brush);
    pRectItem->setPos(pointLoc);
    m_pScene->addItem(pRectItem);
}
