#ifndef CHARACTERVIEW_H
#define CHARACTERVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "character.h"

class CharacterView : public QGraphicsView
{
    Q_OBJECT
public:
    CharacterView(QGraphicsScene *scene, QWidget *parent = 0);
    Character *character;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    int speed;
public slots:
    void tick();

private:
    bool moveRight, moveLeft, moveUp, moveDown;
};

#endif // CHARACTERVIEW_H
