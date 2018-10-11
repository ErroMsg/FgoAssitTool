#ifndef FGOGRAPHICSVIEW_H
#define FGOGRAPHICSVIEW_H
#include <QGraphicsView>

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
};

#endif // FGOGRAPHICSVIEW_H
