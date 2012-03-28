#include "characterview.h"

#include <QFocusEvent>
#include <QProcess>
#include <QScrollBar>
#include <QtDebug>

CharacterView::CharacterView(QGraphicsScene *scene, int level, QWidget *parent) : QGraphicsView(scene, parent)
{
    if (level > 1) {
        setViewportUpdateMode(FullViewportUpdate);
    }
    // No scroll bars
    //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Dark blue background
    setBackgroundBrush(QBrush(QColor(0,0,50)));
    character = 0;
    this->level = level;
}

void CharacterView::tick()
{
    if (character && character->moved) {
        if (level == 3)
        {
            level = -1;
            QProcess::startDetached("mplayer -quiet bwah.mp3");
        }
        centerOn(character);
    }
}
