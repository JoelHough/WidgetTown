#include "Constants.h"
#include "characterview.h"
#include "customproxy.h"
#include "npc.h"
#include "player.h"
#include "tilescene.h"

#include <QtGui/QApplication>
#include <QCalendarWidget>
#include <QLabel>
#include <QTimer>
#include <QtGui>

#include <ctime>
#include <cstdlib>

int main(int argc, char *argv[])
{
    srand((unsigned)time(0));

    QApplication a(argc, argv);

    // Set up a scene with our map
    TileScene scene(":/tileset.png", ":/map.tmx");

    // Add the player
    Player player(":/nerd.png");
    scene.addCharacter(&player);
    player.setFocus();
    player.setPos(14 * TILE_WIDTH, 20 * TILE_HEIGHT);

    // Set up a view of our scene
    CharacterView view(&scene);
    view.character = &player;
    view.scale(2, 2);
    view.setRenderHints(view.renderHints() | QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    view.resize(800, 600);
    scene.setFocus();

    // We need some friends
    NPC chris(":/nerd.png");
    scene.addCharacter(&chris);
    chris.setPos(14 * TILE_WIDTH, 30 * TILE_HEIGHT);

    NPC joe(":/nerd.png");
    scene.addCharacter(&joe);
    joe.setPos(15 * TILE_WIDTH, 30 * TILE_HEIGHT);

    NPC jim(":/nerd.png");
    scene.addCharacter(&jim);
    jim.setPos(12 * TILE_WIDTH, 30 * TILE_HEIGHT);

    NPC matt(":/nerd.png");
    scene.addCharacter(&matt);
    matt.setPos(14 * TILE_WIDTH, 35 * TILE_HEIGHT);

    // Set up frame timer
    QTimer *frameTimer = new QTimer();
    view.connect(frameTimer, SIGNAL(timeout()), &view, SLOT(tick()));
    scene.connect(frameTimer, SIGNAL(timeout()), &scene, SLOT(tick()));
    frameTimer->start(1000 / 30);

    //------LABEL WIDGET------
    CustomProxy *desk = new CustomProxy(0, Qt::Window);
    desk->setWidget(new QLabel("I'm a Banana!"));
    desk->setScale(.10);
    desk->setPos(TILE_WIDTH / 2 +(9 * TILE_WIDTH), TILE_HEIGHT / 2 + (7 * TILE_HEIGHT));
    desk->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    desk->setZValue(LAYER_COUNT);
    scene.addItem(desk);

    //------CALENDAR WIDGET------
    CustomProxy *proxy = new CustomProxy(0, Qt::Window);
    proxy->setWidget(new QCalendarWidget);
    proxy->setScale(.10);
    proxy->setPos(TILE_WIDTH / 2 +(16 * TILE_WIDTH), TILE_HEIGHT / 2 + (4 * TILE_HEIGHT));
    proxy->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    proxy->setZValue(LAYER_COUNT);
    scene.addItem(proxy);


    view.centerOn(&player);
    view.show();
    return a.exec();
}
