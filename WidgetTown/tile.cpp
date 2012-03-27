#include "tile.h"
#include "Constants.h"
#include <QPainter>
#include <QtDebug>

Tile::Tile(int width, int height, QGraphicsItem *parent) : QGraphicsLayoutItem(), QGraphicsItem(parent)
{
    w = width;
    h = height;
    for (int i = 0; i < LAYER_COUNT; i++) {
        tilestack[i] = 0;
    }
    //qDebug() << "Pix: " << pix->width() << "x" << pix->height();
    setGraphicsItem(this);
}

Tile::~Tile() {}
void paintTile(QPainter *painter, QPixmap *tilePix)
{
    if (tilePix) {
        painter->drawPixmap(0,0,tilePix->width(),tilePix->height(),*tilePix);
    }
}

void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //Q_UNUSED(widget);
    Q_UNUSED(option);
    qDebug() << widget;
    for (int i = 0; i < LAYER_COUNT; i++) {
        paintTile(painter, tilestack[i]);
        if (i == CHARACTER_LAYER) {
            // TODO: Draw characters here
        }
    }
}

QRectF Tile::boundingRect() const
{
    return QRectF(QPointF(0,0), geometry().size());
}

void Tile::setGeometry(const QRectF &rect)
{
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(rect);
    setPos(rect.topLeft());
}

QSizeF Tile::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    switch (which) {
    case Qt::MinimumSize:
    case Qt::PreferredSize:
    case Qt::MaximumSize:
        return QSizeF(w, h);
    default:
        break;
    }
    return constraint;
}

