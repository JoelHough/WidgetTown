#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsItem>
#include <QPainterPath>
#include <QPixmap>

class Character : public QGraphicsItem
{
public:
    Character(QString charsheet, QGraphicsItem *parent = 0);
    ~Character();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void tick(qreal elapsedSeconds); // Game ticked, update state
    QPainterPath shape() const;

    bool moved; // Did we move last tick?
    bool animed; // Did we animated last tick?

protected:
    virtual void oof() {};
    int current_anim;
    int current_frame;
    qreal frame_time;
    int guyWidth;
    int guyHeight;
    qreal speed;
    bool movingRight, movingLeft, movingUp, movingDown;

private:
    QPixmap *charsheet;
    QPainterPath shapePath;
};

#endif // CHARACTER_H
