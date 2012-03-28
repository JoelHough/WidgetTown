#include <QtGui/QApplication>
#include <QCalendarWidget>
#include <QX11EmbedWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBrush>
#include <QColor>
#include <QTimer>
#include <QtGui>

#include "tilescene.h"
#include "characterview.h"
#include "customproxy.h"

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
    //-----X11 Embed WIDGET------

    //CustomProxy *embed = new CustomProxy(0, Qt::Window);
//    embed->setWidget(new QX11EmbedContainer);
//    embed->setScale(.10);
//    embed->setPos(16+(14*32), 16+(8*32));
//    embed->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
//    embed->show();


    QX11EmbedContainer container;
    container.show();


    QProcess * process = new QProcess(&container);
    container.show();
    QString executable("xterm");
    QStringList arguments;
    arguments << "-into";
    arguments << QString::number(container.winId());
    process->start(executable, arguments);
    container.embedClient(container.winId());
    //scene.addItem(embed);



    //------CALENDAR WIDGET------
    CustomProxy *proxy = new CustomProxy(0, Qt::Window);
    proxy->setWidget(new QCalendarWidget);
    proxy->setScale(.10);
    proxy->setPos(16 +(16 * 32), 16 + (4 *32));
    QRectF rect = proxy->boundingRect();
    proxy->setCacheMode(QGraphicsItem::DeviceCoordinateCache);

    scene.addItem(proxy);
    //        }
    //    }
    //    scene.setSceneRect(scene.itemsBoundingRect());

    //QGraphicsView view(&scene);
    view.scale(2, 2);
    view.setRenderHints(view.renderHints() | QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    view.setBackgroundBrush(QPixmap(":/No-Ones-Laughing-3.jpg"));
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.show();
    // Size and show
    view.resize(800, 600);
    view.show();
    return a.exec();
}
