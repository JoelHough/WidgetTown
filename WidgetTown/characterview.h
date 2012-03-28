#ifndef CHARACTERVIEW_H
#define CHARACTERVIEW_H

#include "character.h"

#include <QGraphicsView>

class CharacterView : public QGraphicsView
{
    Q_OBJECT
public:
    CharacterView(QGraphicsScene *scene, int level = 1, QWidget *parent = 0);
    Character *character;

public slots:
    void tick();

private:
    int level;

};

#endif // CHARACTERVIEW_H
