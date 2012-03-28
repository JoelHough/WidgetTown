#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsItem>
#include <QPixmap>

class Character : public QGraphicsItem
{
public:
    Character(QPixmap *charsheet, QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    int guyWidth;
    int guyHeight;

private:
    QPixmap *charsheet;
};

#endif // CHARACTER_H
