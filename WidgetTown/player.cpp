#include "player.h"

#include <QKeyEvent>

#include <QtDebug>

Player::Player(QString charsheet, QGraphicsPixmapItem *parent) : Character(charsheet, parent)
{
    setFlag(ItemIsFocusable);
}

void Player::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_D:
        movingRight = true;
        break;
    case Qt::Key_S:
        movingDown = true;
        break;
    case Qt::Key_A:
        movingLeft = true;
        break;
    case Qt::Key_W:
        movingUp = true;
        break;
    default:
        break;
    }
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_D:
        movingRight = false;
        break;
    case Qt::Key_S:
        movingDown = false;
        break;
    case Qt::Key_A:
        movingLeft = false;
        break;
    case Qt::Key_W:
        movingUp = false;
        break;
    default:
        break;
    }
}
