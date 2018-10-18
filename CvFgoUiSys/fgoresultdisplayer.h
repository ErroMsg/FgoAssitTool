#ifndef FGORESULTDISPLAYER_H
#define FGORESULTDISPLAYER_H
#include "fgodisplayerwidget.h"
#include <QPoint>

class QGraphicsItem;
class FgoResultDisplayer : public FgoDisplayerWidget
{
public:
    FgoResultDisplayer(QString strTitle,QWidget *parent = nullptr);

    void postMatResult(QPoint pt,int width, int height);
};

#endif // FGORESULTDISPLAYER_H
