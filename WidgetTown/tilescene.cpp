#include "tilescene.h"
#include "tile.h"

#include <QGraphicsGridLayout>
#include <QtDebug>
#include <QXmlStreamReader>
#include <QFile>
#include <QColor>
#include <QBitmap>

void readLayer(QXmlStreamReader &xml, QGraphicsGridLayout *grid, QList<QPixmap*> &tiles, int layer)
{
    for (int y = 0; y < 100; y++)
    {
        for (int x = 0; x < 100; x++)
        {
            do {
                xml.readNext();
            } while (!xml.isStartElement() || xml.name() != "tile");
            int id = xml.attributes().at(0).value().toString().toInt();
            //qDebug() << "Tile ID:" << id;
            // tmx tile ids are 1-based with 0 indicating no tile
            if (id) {
                ((Tile*)grid->itemAt(y, x))->tilestack[layer] = tiles.at(id - 1);
            }
        }
    }
}

TileScene::TileScene(QGraphicsWidget *parent) :
    QGraphicsWidget(parent)
{
    // Load the tileset.png resource into the tile list
    QImage img;
    img.load(":/tileset.png");
    QImage mask = img.createMaskFromColor(QColor(255, 255, 255).rgb());//, Qt::MaskOutColor);
    qDebug() << "Img: " << img.width() << "x" << img.height();
    for (int y = 0; y < img.height() / 32; y++)
    {
        for (int x = 0; x < img.width() / 32; x++)
        {
            QPixmap *tilepix = new QPixmap(QPixmap::fromImage(img.copy(x * 32, y * 32, 32, 32)));
            tilepix->setMask(QBitmap::fromImage(mask.copy(x * 32, y * 32, 32, 32)));
            tiles.push_back(tilepix);
        }
    }
    qDebug() << "Tiles loaded: " << tiles.size() << "(" << img.width() / 32 << "x" << img.height() / 32 << ")";

    // Read map data
    qDebug() << "Opening the map file";
    QFile* file = new QFile(":/map.tmx");
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    QXmlStreamReader xml(file);

    // Find first "layer" tag (ground)
    do {
        xml.readNext();
    } while (xml.name() != "layer");
    xml.readNext(); // Now at "data" tag
    // Parser will be at tile data at next read

    qDebug() << "Filling the grid";
    // Fill the grid with tile objects
    QGraphicsGridLayout *grid = new QGraphicsGridLayout();
    for (int y = 0; y < 100; y++)
    {
        for (int x = 0; x < 100; x++)
        {
            grid->addItem(new Tile(32, 32), y, x);
        }
    }
    grid->setSpacing(0); // No borders between tiles
    this->setLayout(grid);

    for (int i = 0; i < 4; i++) {
        qDebug() << "Reading layer " << i;
        readLayer(xml, grid, tiles, i);
    }
}

TileScene::~TileScene()
{
    for (int i = 0; i < tiles.count(); i++)
    {
        delete tiles.at(i);
        tiles.replace(i, 0);
    }
    tiles.clear();
}
