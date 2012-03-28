#ifndef CHARACTERVIEW_H
#define CHARACTERVIEW_H

#include "character.h"

#include <QGraphicsView>

class CharacterView : public QGraphicsView
{
    Q_OBJECT
public:
    CharacterView(QGraphicsScene *scene, QWidget *parent = 0);
    Character *character;

public slots:
    void tick();

};

#endif // CHARACTERVIEW_H
