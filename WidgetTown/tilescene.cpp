#include "Constants.h"
#include "tilescene.h"

#include <QBitmap>
#include <QColor>
#include <QFile>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <QXmlStreamReader>

#include <QtDebug>

TileScene::TileScene(QString tileset, QString map, QObject *parent) : QGraphicsScene(parent)
{
  // Load things!
  loadTiles(tileset);
  loadMap(map);

  // Keeps us focus (on the player, for instance) even if we click the background
  setStickyFocus(true);

  // Start the clock!  We now have time since last tick
  frameTimer.start();
}

TileScene::~TileScene()
{
  qDebug() << "Cleaning up TileScene";
  for (int i = 0; i < tiles.count(); i++) {
    delete tiles.at(i);
  }
  tiles.clear();
}

void TileScene::addCharacter(Character *character)
{
  addItem(character); // Add the character, graphically, to the world
  characters.push_back(character); // Add the character, spiritually, to the world
}

void TileScene::tick()
{
  // Update the world!
  qreal elapsedSeconds = frameTimer.restart() / 1000.0; // How long since the last tick?

  // For each character in the world...
  for (int i = 0; i < characters.count(); i++) {
    Character *character = characters.at(i);

    // We're going to be clever and only redraw what we have to.
    QRectF startPos = character->boundingRect(); // This is where they were
    character->tick(elapsedSeconds); // Update the character.  They may move.

    // If the character moved...
    if (character->moved) {
      // Redraw where they were and where they are
      update(startPos);
      update(character->boundingRect());
    }
  }
}

void TileScene::loadTiles(QString filename)
{
  // Load the image from the given path
  QImage img;
  img.load(filename);

  // In the tileset we have, white is the background color.
  // Make a transparency mask where we find white
  QImage mask = img.createMaskFromColor(QColor(255, 255, 255).rgb());

  qDebug() << "Img: " << img.width() << "x" << img.height();

  // For each tile-sized chunk of image...
  // Note the careful handling of x and y.  The indexes in 'tiles' must correspond
  // to the map file tile id's (they are actually off by 1, the map file uses 0 for 'no tile')
  for (int y = 0; y < img.height() / TILE_HEIGHT; y++)
    {
      for (int x = 0; x < img.width() / TILE_WIDTH; x++)
        {
          // Pull out a pixmap for the tile
          QPixmap *tilepix = new QPixmap(QPixmap::fromImage(img.copy(x * TILE_WIDTH,
                                                                     y * TILE_HEIGHT,
                                                                     TILE_WIDTH,
                                                                     TILE_HEIGHT)));
          // Set the transparency mask for the tile
          tilepix->setMask(QBitmap::fromImage(mask.copy(x * TILE_WIDTH,
                                                        y * TILE_HEIGHT,
                                                        TILE_WIDTH,
                                                        TILE_HEIGHT)));
          
          // Add the tile to the list
          tiles.push_back(tilepix);
        }
    }
  qDebug() << "Tiles loaded: " << tiles.size() << "(" << img.width() / TILE_WIDTH << "x" << img.height() / TILE_HEIGHT << ")";
}

void TileScene::loadMap(QString filename)
{
  qDebug() << "Opening the map file";
  QFile* file = new QFile(filename);
  file->open(QIODevice::ReadOnly | QIODevice::Text);
  QXmlStreamReader xml(file);

  // The xml file from the Tiled editor is not very good about putting useful data into the tag attributes.
  // For instance, the 'tile' elements don't list the x/y of the tile!  By convention, the top left tile comes first
  // and proceeds right then down.  Likewise, the first 'layer' section is the lowest Z, followed by higher ones.
  // We exploit this with a very dumb parsing scheme wherein we look forward until
  // we find a <tile>, pull a set number of <tiles> for a layer, then do it again
  // for the next layer.

  for (int z = 0; z < LAYER_COUNT; z++)
    {
      qDebug() << "Reading layer " << z;
      for (int y = 0; y < MAP_HEIGHT; y++)
        {
          for (int x = 0; x < MAP_WIDTH; x++)
            {
              do {
                xml.readNext();
                if (xml.error() != xml.NoError) {
                  qDebug() << "Xml read error: " << xml.errorString();
                  return;
                }
              } while (!xml.isStartElement() || xml.name() != "tile");
              int id = xml.attributes().at(0).value().toString().toInt(); // Tile id
              //qDebug() << "Tile ID:" << id;
              // tmx tile ids are 1-based with 0 indicating no tile
              if (id) {
                // Add a pixmap item to the scene for the tile
                QGraphicsPixmapItem *tile = addPixmap(*tiles.at(id - 1));

                // Caching is good, right?
                tile->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
                tile->setPos(x * TILE_WIDTH, y * TILE_HEIGHT);
                tile->setZValue(z); // Don't forget to set the layer, for the overlays and whatnots
              }
            }
        }
    }
  file->close();
  delete file;
  file = 0;
}
