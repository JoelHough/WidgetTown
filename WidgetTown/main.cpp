#include <QtGui/QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBitmap>
#include <QImage>
#include <QPixmap>
#include <QBrush>
#include <QColor>
#include <QTimer>
#include "tilescene.h"
#include "character.h"
#include "characterview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Set up a scene with our map
    QGraphicsScene scene;
    TileMapWidget *map = new TileMapWidget();
    scene.addItem(map);
    // Load the tileset.png resource into the tile list
    QImage img;
    img.load(":/nerd.png");
    int guyWidth = img.width() / 3;
    int guyHeight = img.height() / 4;
    QImage mask = img.createMaskFromColor(QColor(255, 255, 255).rgb());
    QPixmap *charpix = new QPixmap(QPixmap::fromImage(img));
    charpix->setMask(QBitmap::fromImage(mask.copy(1 * 32, 1 * 32, 32, 32)));
    Character player(charpix);
    scene.addItem(&player);

    // Set up a view of our scene
    CharacterView view(&scene);
    view.character = &player;

    // Focus the map for events
    //map->setFocus();

    // Set up frame timer
    QTimer *frameTimer = new QTimer();
    map->connect(frameTimer, SIGNAL(timeout()), map, SLOT(tick()));
    view.connect(frameTimer, SIGNAL(timeout()), &view, SLOT(tick()));
    frameTimer->start(1000 / 30);

    // Size and show
    view.resize(800, 600);
    view.show();
    return a.exec();
}
