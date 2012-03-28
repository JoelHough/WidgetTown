#ifndef TILESCENE_H
#define TILESCENE_H

#include "character.h"

#include <QElapsedTimer>
#include <QObject>
#include <QGraphicsScene>
#include <QList>
#include <QPixmap>
#include <QString>

class TileScene : public QGraphicsScene
{
    Q_OBJECT
public:
    TileScene(QString tileset, QString map, QObject *parent = 0);
    //~TileScene();

    void addCharacter(Character *character);

public slots:
    void tick();

protected:
    QList<QPixmap*> tiles;
    QList<Character*> characters;
    QElapsedTimer frameTimer;

    void loadTiles(QString filename);
    void loadMap(QString filename);
};

#endif // TILESCENE_H
