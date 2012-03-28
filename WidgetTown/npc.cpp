#include "npc.h"

#include <cstdlib>

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
    direction = -1;
    duration = randomDouble(2.0, 6.0);
    moveTimer.connect(&moveTimer, SIGNAL(timeout()), this, SLOT(push()));
    moveTimer.setSingleShot(true);
    moveTimer.start(int(duration * 1000.0));
}

void NPC::push()
{
    moveTimer.stop();
    if (direction == -1) {
        duration = randomDouble(0.5, 4.0);
        direction = randomInt(0, 3);
    } else {
        duration = randomDouble(2.0, 6.0);
        direction = -1;
    }

    moveDirection();
    moveTimer.start(int(duration * 1000.0));
}

void NPC::oof()
{
    direction = (direction + 1) % 4;
    moveDirection();
}

void NPC::moveDirection()
{
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
