#include "characterview.h"

#include <QColor>
#include <QBrush>
#include <QScrollBar>
#include <QtDebug>
#include <QKeyEvent>

CharacterView::CharacterView(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene, parent)
{
    // No scroll bars
    //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Dark blue background
    setBackgroundBrush(QBrush(QColor(0,0,50)));

    character = 0;
    moveUp = moveLeft = moveDown = moveRight = false;
    speed = 4;
}

void CharacterView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_D:
        moveRight = true;
        break;
    case Qt::Key_S:
        moveDown = true;
        break;
    case Qt::Key_A:
        moveLeft = true;
        break;
    case Qt::Key_W:
        moveUp = true;
        break;
    default:
        break;
    }
}

void CharacterView::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_D:
        moveRight = false;
        break;
    case Qt::Key_S:
        moveDown = false;
        break;
    case Qt::Key_A:
        moveLeft = false;
        break;
    case Qt::Key_W:
        moveUp = false;
        break;
    default:
        break;
    }
}

void CharacterView::tick()
{
    if (character) {
        int dx = 0;
        int dy = 0;

        if (moveUp) dy -= 1;
        if (moveDown) dy += 1;
        if (moveLeft) dx -= 1;
        if (moveRight) dx += 1;

        if (character) {
            character->moveBy(dx * speed, dy * speed);
            horizontalScrollBar()->setValue(character->boundingRect().center().x() - width() / 2);
            verticalScrollBar()->setValue(character->boundingRect().center().y() - height() / 2);
            this->scene()->update();
         }
    }
    qDebug() << horizontalScrollBar()->value();
}
