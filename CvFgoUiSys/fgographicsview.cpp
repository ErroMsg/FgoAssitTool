#include "fgographicsview.h"
//#include "mainwindow.h"
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QScrollBar>
#include <QDebug>

FgoGraphicsView::FgoGraphicsView(QWidget *parent)
    : m_scale(1.0)
    , m_zoomDelta(0.2)
    , m_bMouseTranslate(false)
    ,m_translateSpeed(1.0)
{
    setBackgroundBrush(QColor(80,80,80));
    setMouseTracking(true);
    //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHint(QPainter::Antialiasing);
}

void FgoGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bMouseTranslate)
    {
        //QPointF mouseDelta = mapToScene(event->pos()) - mapToScene(m_lastMousePos);
        QPoint deltapt = event->pos() - m_lastMousePos;

        QScrollBar *pvBar = this->verticalScrollBar();
        pvBar->setValue(pvBar->value() - deltapt.y());

        QScrollBar *phBar = this->horizontalScrollBar();
        phBar->setValue(phBar->value() - deltapt.x());
    }
    m_lastMousePos = event->pos();

    upDateCoordInfo(event);
    QGraphicsView::mouseMoveEvent(event);
}

void FgoGraphicsView::wheelEvent(QWheelEvent *event)
{
    QPoint scrollAmount = event->angleDelta();
    scrollAmount.y() > 0 ? zoomIn() : zoomOut();
    QGraphicsView::wheelEvent(event);
}

void FgoGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bMouseTranslate = true;
        m_lastMousePos = event->pos();
    }
    QGraphicsView::mousePressEvent(event);
}

void FgoGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    m_bMouseTranslate = false;
    QGraphicsView::mouseReleaseEvent(event);
}

void FgoGraphicsView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
}

void FgoGraphicsView::zoomIn()
{
    zoom(1 + m_zoomDelta);
}

void FgoGraphicsView::zoomOut()
{
    zoom(1 - m_zoomDelta);
}

void FgoGraphicsView::zoom(float scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).
            mapRect(QRectF(0, 0, 1, 1)).width();

    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
    m_scale *= scaleFactor;

}

void FgoGraphicsView::upDateCoordInfo(QMouseEvent *event)
{
    QPoint viewPoint = event->pos();
    QPointF scenePoint = mapToScene(viewPoint);

    QString strCoord = QString("ViewPos:(%1,%2),ScenePos:(%3,%4),")
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
}
