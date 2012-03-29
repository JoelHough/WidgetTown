/*!
  \file   character.cpp
  \author Team Exception
  \date   Wed Mar 28 17:33:44 2012
    
*/
#include "Constants.h"
#include "character.h"

#include <QImage>
#include <QList>
#include <QPainter>
#include <QKeyEvent>

#include <QtDebug>

Character::Character(QString charsheet, QGraphicsItem *parent) : QGraphicsItem(parent)
{
  // Load the image and turn it into a pixmap which is what we need for our internal functions.  Character sheets already have an alpha channel, so no need to do color keying
  QImage img;
  img.load(charsheet);
  this->charsheet = new QPixmap(QPixmap::fromImage(img));

  // Figure out the individual frame sizes
  guyWidth = this->charsheet->width() / CHARACTER_SHEET_FRAMES;
  guyHeight = this->charsheet->height() / CHARACTER_SHEET_ANIMS;

  // Default to global speed
  speed = CHARACTER_SPEED;

  // No movement to start with
  movingUp = movingLeft = movingDown = movingRight = false;
  moved = false;

  // Place us at character Z level for proper overlapping
  setZValue(CHARACTER_LAYER);

  // These will be reset to a real anim and frame next update.
  current_anim = CHARACTER_SHEET_DEFAULT_ANIM;
  current_frame = CHARACTER_SHEET_DEFAULT_FRAME;

  // Haven't animated, no frame time elapsed
  animed = false;
  frame_time = 0;

  // Collision shape is a small elipse around the feet
  shapePath.addEllipse(QRectF(3,24, guyWidth - 6, guyHeight / 2));
}

Character::~Character()
{
  qDebug() << "Cleaning up Character";
  delete charsheet;
}

QRectF Character::boundingRect() const
{
  return QRectF(0,0, guyWidth, guyHeight); // 0-origin rect the size of a frame
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(option);
  Q_UNUSED(widget);

  // Draw the section of the charsheet for the current animation and frame
  painter->drawPixmap(0, 0,
                      *charsheet,
                      guyWidth * CHARACTER_SHEET_WALK_FRAMES[current_frame],
                      guyHeight * current_anim,
                      guyWidth, guyHeight);
}

void Character::tick(qreal elapsedSeconds)
{
  int dx = 0; // Direction of x travel
  int dy = 0; // Direction of y travel

  if (movingUp) dy -= 1;
  if (movingDown) dy += 1;
  if (movingLeft) dx -= 1;
  if (movingRight) dx += 1;

  bool hit = false; // Ran into something?
  moved = dx != 0 || dy != 0; // Did we move?
  if (moved) {
    QPointF startpos = pos(); // We are currently here
    QList<QGraphicsItem*> hits; // We intersect these things

    // Try to move by x, then y.  If we hit something, unmove.

    moveBy(dx * speed * elapsedSeconds, 0); // Just x move first
    hits = collidingItems();
    for (int i = 0; i < hits.count(); i++) {

      // If we are intersecting something in our layer...
      if (hits.at(i)->zValue() == zValue()) {
        // Step back and make a note of it
        setPos(startpos);
        hit = true;
      }
    }

    startpos = pos(); // We are now here
    moveBy(0, dy * speed * elapsedSeconds); // Just the y now
    hits = collidingItems();
    for (int i = 0; i < hits.count(); i++) {
      // If we are intersecting something in our layer...
      if (hits.at(i)->zValue() == zValue()) {
        // Step back and make a note of it
        setPos(startpos);
        hit = true;
      }
    }

    if (hit) oof(); // Oof! We hit something! Let our subclasses know.

    frame_time += elapsedSeconds; // We're moving, so update the frame timer
  }

  // Figure out which animation to use based on movement direction
  if (movingDown) {
    current_anim = CHARACTER_SHEET_WALK_DOWN_ANIM;
  } else if (movingUp) {
    current_anim = CHARACTER_SHEET_WALK_UP_ANIM;
  } else if (movingRight) {
    current_anim = CHARACTER_SHEET_WALK_RIGHT_ANIM;
  } else if (movingLeft) {
    current_anim = CHARACTER_SHEET_WALK_LEFT_ANIM;
  }

  animed = false; // Did we do any animating this update?

  // If we want the default animation...
  if (current_anim == CHARACTER_SHEET_DEFAULT_ANIM) {
    // Use the WALK_DOWN animation
    current_anim = CHARACTER_SHEET_WALK_DOWN_ANIM;
    animed = true;
  }

  // If we want the default frame...
  if (current_frame == CHARACTER_SHEET_DEFAULT_FRAME) {
    // Use the first one
    current_frame = 0;
    animed = true;
  }

  // While it has been too long since we last updated the frame...
  // This is a 'while' instead of an 'if' so we can catch up with slow updates
  // without rendering all the frames we missed
  while (frame_time > CHARACTER_FRAME_TIME) {
    frame_time -= CHARACTER_FRAME_TIME; // One frame into the future!

    // Next frame in the animation, looping back if we reach the end
    current_frame = (current_frame + 1) % CHARACTER_SHEET_WALK_FRAME_COUNT;
    animed = true;
  }
}

QPainterPath Character::shape() const
{
  return shapePath; // Our pre-calculated collision shape
}
