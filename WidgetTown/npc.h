/*!
  \class NPC
  \file   npc.h
  \author  Team Exception
  \date   Wed Mar 28 17:59:43 2012
  
  \brief  A meandering NPC
  
  
*/
#ifndef NPC_H
#define NPC_H

#include "character.h"

#include <QObject>
#include <QTimer>

class NPC : public QObject, public Character
{
  Q_OBJECT
  
public:
  NPC(QString charsheet, QGraphicsItem *parent = 0);

public slots:
  void push(); // Tells the NPC to move

protected:
  virtual void oof();
  void moveDirection(); // Sets the moving* bools based on 'direction' int

  int direction; // Direction we're moving, -1 for not moving.
  qreal duration; // Hold long to hold this heading
  QTimer moveTimer; // Tells us when to move
};

#endif // NPC_H
