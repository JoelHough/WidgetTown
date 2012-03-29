#include "npc.h"

#include <cstdlib>

// Bunch of random utilities
double randomDouble()
{
  return rand() / (double(RAND_MAX) + 1.0);
}

double randomDouble(double max)
{
  return randomDouble() * max;
}

double randomDouble(double min, double max)
{
  return randomDouble() * (max - min) + min;
}

int randomInt(int min, int max)
{
  return int(randomDouble() * (max - min) + min);
}

NPC::NPC(QString charsheet, QGraphicsItem *parent) : QObject(), Character(charsheet, parent)
{
  direction = -1; // Not moving to start with
  duration = randomDouble(2.0, 6.0); // Stand here for a while

  // The moveTimer compels us
  moveTimer.connect(&moveTimer, SIGNAL(timeout()), this, SLOT(push()));
  moveTimer.setSingleShot(true); // We reset this with a new duration manually
  moveTimer.start(int(duration * 1000.0)); // Start the clock (note msec conversion)
}

void NPC::push()
{
  moveTimer.stop(); // Stop the clock!

  // If we're just standing here...
  if (direction == -1) {
    // Move somewhere for a bit
    duration = randomDouble(0.5, 4.0);
    direction = randomInt(0, 3);
  } else { // If we're on the move...
    // Take a breather
    duration = randomDouble(2.0, 6.0);
    direction = -1;
  }

  moveDirection(); // Set the moving* bools
  moveTimer.start(int(duration * 1000.0)); // Start the clock!
}

void NPC::oof()
{
  // Oh noes!!! We hit something!

  // Abruptly change course
  direction = (direction + 1) % 4;
  moveDirection();
}

void NPC::moveDirection()
{
  // Set up the moving* bools so that our superclass gets us walking
  movingRight = movingLeft = movingUp = movingDown = false;
  switch (direction) {
  case 0:
    movingRight = true;
    break;
  case 1:
    movingLeft = true;
    break;
  case 2:
    movingUp = true;
    break;
  case 3:
    movingDown = true;
    break;
  default:
    break;
  }
}
