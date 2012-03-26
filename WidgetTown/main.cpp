#include <QtGui/QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBrush>
#include <QColor>
#include "tilescene.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene;
    TileScene *map = new TileScene();
    scene.addItem(map);
    QGraphicsView view(&scene);
    view.setBackgroundBrush(QBrush(QColor(0,0,50)));
    view.resize(800, 600);
    view.show();
    return a.exec();
}
