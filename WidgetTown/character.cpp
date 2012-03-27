#include "character.h"

#include <QPainter>

Character::Character(QPixmap *charsheet, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    this->charsheet = charsheet;
}

QRectF Character::boundingRect()
{
    return QRectF(0,0, 32,32);
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(0,0,*charsheet);
}
