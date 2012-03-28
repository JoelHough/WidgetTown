#include "characterview.h"

#include <QScrollBar>
#include <QtDebug>

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
    if (character && character->moved) {
        horizontalScrollBar()->setValue((character->x() + character->boundingRect().width() / 2) * 2 - width() / 2);
        verticalScrollBar()->setValue((character->y() + character->boundingRect().height() / 2) * 2 - height() / 2);
    }
}
