#ifndef FGOGRAPHICSVIEW_H
#define FGOGRAPHICSVIEW_H
#include <QGraphicsView>
#include "cvmatchhelper.h"
class QMouseEvent;
class QWheelEvent;
class FgoGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit FgoGraphicsView(QWidget *parent = 0);
signals:
    void Signal_UpdateCoor(QString);
protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    void zoomIn();
    void zoomOut();
    void zoom(float scaleFactor);
    void upDateCoordInfo(QMouseEvent *event);
    void translate(QPointF delta);  // 平移

private:
    qreal m_scale;
    qreal m_translateSpeed; // 平移速度
    qreal m_zoomDelta; // 缩放的增量
    QPoint m_lastMousePos; // 鼠标最后按下的位置
    bool m_bMouseTranslate;

};

#endif // FGOGRAPHICSVIEW_H
