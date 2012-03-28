#ifndef TILE_H
#define TILE_H

#include "Constants.h"
#include <QGraphicsLayoutItem>
#include <QGraphicsItem>
#include <QPixmap>
#include "tilescene.h"

class Tile : public QGraphicsLayoutItem, public QGraphicsItem
{
public:
    explicit Tile(int width, int height, TileMapWidget *tilemap, QGraphicsItem *parent = 0);
    ~Tile();

    void setGeometry(const QRectF &rect);
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    QPixmap* tilestack[LAYER_COUNT];
private:
    int w, h;
};

#endif // TILE_H
