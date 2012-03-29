/*!
  \class CharacterView
  \file   characterview.h
  \author  <joel@defenestrator>
  \date   Wed Mar 28 18:25:03 2012
  
  \brief  A graphics view that can follow a character, like an omniscient stalker!
  
  
*/
#ifndef CHARACTERVIEW_H
#define CHARACTERVIEW_H

#include "character.h"

#include <QGraphicsView>

class CharacterView : public QGraphicsView
{
  Q_OBJECT
  public:
  CharacterView(QGraphicsScene *scene,
                int level = 1, // You're waiting for a train...
                QWidget *parent = 0);
  Character *character; // Who we're stalking

public slots:
  void tick(); // Update the scenery (focus on the character) 

private:
  int level; // A train that will take you far away...

};

#endif // CHARACTERVIEW_H
