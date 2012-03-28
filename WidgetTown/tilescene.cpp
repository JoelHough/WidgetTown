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
    loadTiles(tileset);
    loadMap(map);
    setStickyFocus(true);
    frameTimer.start();
}

void TileScene::addCharacter(Character *character)
{
    addItem(character);
    characters.push_back(character);
}

void TileScene::tick()
{
    qreal elapsedSeconds = frameTimer.restart() / 1000.0;
    for (int i = 0; i < characters.count(); i++) {
        Character *character = characters.at(i);
        QRectF startPos = character->boundingRect();
        character->tick(elapsedSeconds);
        if (character->moved) {
            update(startPos);
            update(characters.at(i)->boundingRect());
        }
    }
}

void TileScene::loadTiles(QString filename)
{
    QImage img;
    img.load(filename);
    QImage mask = img.createMaskFromColor(QColor(255, 255, 255).rgb());
    qDebug() << "Img: " << img.width() << "x" << img.height();
    for (int y = 0; y < img.height() / TILE_HEIGHT; y++)
    {
        for (int x = 0; x < img.width() / TILE_WIDTH; x++)
        {
            QPixmap *tilepix = new QPixmap(QPixmap::fromImage(img.copy(x * TILE_WIDTH, y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT)));
            tilepix->setMask(QBitmap::fromImage(mask.copy(x * TILE_WIDTH, y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT)));
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
    // We exploit this with a very dumb parsing scheme.

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
                    QGraphicsPixmapItem *tile = addPixmap(*tiles.at(id - 1));
                    tile->setPos(x * TILE_WIDTH, y * TILE_HEIGHT);
                    tile->setZValue(z);
                }
            }
        }
    }
}
