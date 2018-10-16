#include "fgoresultdisplayer.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPen>

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
    QPen pen;
    pen.setColor(QColor(255,0,0));
    pen.setWidth(5);
    pRectItem->setPen(pen);
    pRectItem->setPos(pointLoc);
    m_pScene->addItem(pRectItem);
}
