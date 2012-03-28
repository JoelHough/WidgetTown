#include "character.h"

#include <QPainter>
#include <QKeyEvent>

Character::Character(QPixmap *charsheet, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    this->charsheet = charsheet;
    guyWidth = charsheet->width() / 3;
    guyHeight = charsheet->height() / 4;
}

QRectF Character::boundingRect() const
{
    return QRectF(x(), y(), guyWidth, guyHeight);
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(0,0,*charsheet, guyWidth * 1, guyHeight * 2, guyWidth, guyHeight);
}
