/*!
  \class TileScene
  \file   tilescene.h
  \author  Team Exception
  \date   Wed Mar 28 18:08:33 2012
  
  \brief  A QGraphicsScene that draws a tilemap and can have Characters on it
  
  
*/
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
  TileScene(QString tileset, // Path to tileset image
            QString map, // Path to Tiled .mpx Xml file
            QObject *parent = 0);
  ~TileScene();

  // Add a character to the map.  Be sure to use this instead of addItem so
  // characters get tick updates!
  void addCharacter(Character *character);

public slots:
  void tick(); // Tick the world a frame forward

protected:
  QList<QPixmap*> tiles; // Our tile images, handily indexed
  QList<Character*> characters; // All the crazy characters in the world
  QElapsedTimer frameTimer; // Keeps track of how long since last tick

  void loadTiles(QString filename); // Load up the tiles
  void loadMap(QString filename); // Load up the map
};

#endif // TILESCENE_H
