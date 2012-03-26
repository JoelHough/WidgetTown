#ifndef TILE_H
#define TILE_H

#include <QGraphicsLayoutItem>
#include <QGraphicsItem>
#include <QPixmap>

#define LAYER_COUNT 5
class Tile : public QGraphicsLayoutItem, public QGraphicsItem
{
public:
    explicit Tile(int width, int height, QGraphicsItem *parent = 0);
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
