/*!
  \class Character
  \file   character.h
  \author  Team Exception
  \date   Wed Mar 28 17:16:52 2012
  
  \brief  Animated, collidable character
  
  
*/
#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsItem>
#include <QPainterPath>
#include <QPixmap>

class Character : public QGraphicsItem
{
public:

  Character(QString charsheet, // Path to charsheet image
            QGraphicsItem *parent = 0);
  ~Character();

  // QGraphicsItem functions
  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  QPainterPath shape() const;

  void tick(qreal elapsedSeconds); // Update this character, given seconds from last update

  bool moved; // Did we move last tick?
  bool animed; // Did we animated last tick?

protected:
  virtual void oof() // Called when moving causes a collision
  {}

  int current_anim; // Current walking animation.  Set to one of Constants.h's CHARACTER_SHEET_*_ANIM
  int current_frame; // Current walking animation frame index.  Used as an index into Constant.h's CHARACTER_SHEET_WALK_FRAMES.  Must be in range -1 to (CHARACTER_SHEET_WALK_FRAME_COUNT-1)
  qreal frame_time; // How long each frame will be displayed be changing
  int guyWidth; // The width of one character sheet frame
  int guyHeight; // The height of one character sheet frame
  qreal speed; // The movement speed of the character.  In pixels/second
  bool movingRight, movingLeft, movingUp, movingDown; // Set these to make the character move.

private:
  QPixmap *charsheet; // Our character sheet
  QPainterPath shapePath; // The collision shape
};

#endif // CHARACTER_H
