#include "fgographicsview.h"
//#include "mainwindow.h"
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QDebug>

#define VIEW_CENTER viewport()->rect().center()
#define VIEW_WIDTH viewport()->rect().width()
#define VIEW_HEIGHT viewport()->rect().height()

FgoGraphicsView::FgoGraphicsView(QWidget *parent)
    : m_scale(1.0)
    , m_zoomDelta(0.2)
    , m_bMouseTranslate(false)
    ,m_translateSpeed(1.0)
{
    setBackgroundBrush(QColor(80,80,80));
    setMouseTracking(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setCursor(Qt::PointingHandCursor);
    setRenderHint(QPainter::Antialiasing);
    setSceneRect(INT_MIN/2, INT_MIN/2, INT_MAX, INT_MAX);
    centerOn(0, 0);
}

void FgoGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bMouseTranslate)
    {
        QPointF mouseDelta = mapToScene(event->pos()) - mapToScene(m_lastMousePos);
        translate(mouseDelta);
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

void FgoGraphicsView::translate(QPointF delta)
{
    // 根据当前 zoom 缩放平移数
    delta *= m_scale;
    delta *= m_translateSpeed; // view 根据鼠标下的点作为锚点来定位 scene
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    QPoint newCenter(VIEW_WIDTH / 2 - delta.x(), VIEW_HEIGHT / 2 - delta.y());
    centerOn(mapToScene(newCenter)); // scene 在 view 的中心点作为锚点
    setTransformationAnchor(QGraphicsView::AnchorViewCenter);
}
