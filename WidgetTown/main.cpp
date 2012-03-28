#include <QtGui/QApplication>
#include <QCalendarWidget>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QBitmap>
#include <QImage>
#include <QPixmap>
#include <QBrush>
#include <QColor>
#include <QTimer>
#include <QList>
#include <QtGui>
#include "tilescene.h"
#include "player.h"
#include "character.h"
#include "characterview.h"
#include "customproxy.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Set up a scene with our map
    TileScene scene(":/tileset.png", ":/map.tmx");

    Player player(":/nerd.png");
    scene.addCharacter(&player);
    player.setFocus();

    //    // Load the tileset.png resource into the tile list
//    QImage img;
//    img.load(":/nerd.png");
//    int guyWidth = img.width() / 3;
//    int guyHeight = img.height() / 4;
//    QImage mask = img.createMaskFromColor(QColor(255, 255, 255).rgb());
//    QPixmap *charpix = new QPixmap(QPixmap::fromImage(img));
//    charpix->setMask(QBitmap::fromImage(mask.copy(1 * 32, 1 * 32, 32, 32)));
//    Character player(charpix);
//    scene.addItem(&player);

    // Set up a view of our scene
    CharacterView view(&scene);
    scene.setFocus();
    view.character = &player;

    //view.character = &player;

    // Focus the map for events
    //map->setFocus();

    // Set up frame timer
    QTimer *frameTimer = new QTimer();
    view.connect(frameTimer, SIGNAL(timeout()), &view, SLOT(tick()));
    scene.connect(frameTimer, SIGNAL(timeout()), &scene, SLOT(tick()));
    frameTimer->start(1000 / 30);
    /*
    //QString executable("xterm");
    //QStringList arguments;
    CustomProxy *desk = new CustomProxy(0, Qt::Window);
    desk->setWidget(new QLabel("I'm a Banana!"));
    desk->setScale(.10);
    desk->setPos(16 +(9 * 32), 16 + (7 *32));
    //scene.addWidget(&container);
    desk->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    //container.update();
    scene.addItem(desk);
    //container.activateWindow();
    //------CALENDAR WIDGET------
    CustomProxy *proxy = new CustomProxy(0, Qt::Window);
    proxy->setWidget(new QCalendarWidget);
    proxy->setScale(.10);
    proxy->setPos(16 +(16 * 32), 16 + (4 *32));

    proxy->setCacheMode(QGraphicsItem::DeviceCoordinateCache);

    scene.addItem(proxy);
    //        }
    //    }
    //    scene.setSceneRect(scene.itemsBoundingRect());

    //QGraphicsView view(&scene);*/
    view.scale(2, 2);
    view.setRenderHints(view.renderHints() | QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    // Size and show
    view.resize(800, 600);
    view.show();
    return a.exec();
}
