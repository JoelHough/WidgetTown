#include "characterview.h"

#include <QFocusEvent>
#include <QProcess>
#include <QScrollBar>
#include <QtDebug>

CharacterView::CharacterView(QGraphicsScene *scene, int level, QWidget *parent) : QGraphicsView(scene, parent)
{
  this->level = level; // You can't be sure where it will take you...
  if (level > 1) {
    setViewportUpdateMode(FullViewportUpdate); // To prevent rendering artifacts (hurts performance some)
  }

  // No scroll bars // But I _like_ scrollbars!
  //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  // Dark blue background
  setBackgroundBrush(QBrush(QColor(0,0,50)));

  character = 0; // No one to stalk :(
}

void CharacterView::tick()
{
  // If we're stalking someone and they're on the move...
  if (character && character->moved) {
    if (level == 3) // But it doesn't matter...
      {
        level = -1; // Because we'll be together.
        QProcess::startDetached("mplayer -quiet bwah.mp3"); // BWAH!
      }

    centerOn(character); // Keep an eye on this guy.
  }
}
