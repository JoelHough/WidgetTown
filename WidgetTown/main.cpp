#include <QtGui/QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBrush>
#include <QColor>
#include <QTimer>

#include "tilescene.h"
#include "characterview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Set up a scene with our map
    QGraphicsScene scene;
    TileScene *map = new TileScene();
    scene.addItem(map);

    // Set up a view of our scene
    CharacterView view(&scene);

    // Focus the map for events
    map->setFocus();

    // Set up frame timer
    QTimer *frameTimer = new QTimer();
    map->connect(frameTimer, SIGNAL(timeout()), map, SLOT(tick()));
    view.connect(frameTimer, SIGNAL(timeout()), &view, SLOT(tick()));
    frameTimer->start(1000 / 20);

    // Size and show
    view.resize(800, 600);
    view.show();
    return a.exec();
}
