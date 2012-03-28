#include "characterview.h"

#include <QColor>
#include <QBrush>
#include <QScrollBar>

CharacterView::CharacterView(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene, parent)
{
    // No scroll bars
    //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Dark blue background
    setBackgroundBrush(QBrush(QColor(0,0,50)));
}

void CharacterView::tick()
{
    //horizontalScrollBar()->setValue(horizontalScrollBar()->value() - 1);
}
