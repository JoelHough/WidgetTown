#include "Constants.h"
#include "character.h"

#include <QImage>
#include <QList>
#include <QPainter>
#include <QKeyEvent>

#include <QtDebug>

Character::Character(QString charsheet, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    QImage img;
    img.load(charsheet);
    this->charsheet = new QPixmap(QPixmap::fromImage(img));

    guyWidth = this->charsheet->width() / CHARACTER_SHEET_FRAMES;
    guyHeight = this->charsheet->height() / CHARACTER_SHEET_ANIMS;

    speed = CHARACTER_SPEED;

    movingUp = movingLeft = movingDown = movingRight = false;
    moved = false;

    setZValue(CHARACTER_LAYER);

    current_anim = current_frame = -1;
    frame_time = 0;

    shapePath.addEllipse(QRectF(3,24, guyWidth - 6, guyHeight / 2));
}

Character::~Character()
{
    qDebug() << "Cleaning up Character";
    delete charsheet;
}

QRectF Character::boundingRect() const
{
    return QRectF(0,0, guyWidth, guyHeight);
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(0,0,*charsheet, guyWidth * CHARACTER_SHEET_WALK_FRAMES[current_frame], guyHeight * current_anim, guyWidth, guyHeight);
}

void Character::tick(qreal elapsedSeconds)
{
    int dx = 0;
    int dy = 0;

    if (movingUp) dy -= 1;
    if (movingDown) dy += 1;
    if (movingLeft) dx -= 1;
    if (movingRight) dx += 1;
    bool hit = false;
    moved = dx != 0 || dy != 0;
    if (moved) {
        QPointF startpos;
        QList<QGraphicsItem*> hits;
        // Try to move by x, then y.  If we hit something, unmove.
        startpos = pos();
        moveBy(dx * speed * elapsedSeconds, 0);
        hits = collidingItems();
        for (int i = 0; i < hits.count(); i++) {
            if (hits.at(i)->zValue() == zValue()) {
                setPos(startpos);
                hit = true;
            }
        }

        startpos = pos();
        moveBy(0, dy * speed * elapsedSeconds);
        hits = collidingItems();
        for (int i = 0; i < hits.count(); i++) {
            if (hits.at(i)->zValue() == zValue()) {
                setPos(startpos);
                hit = true;
            }
        }

        if (hit) oof();
        frame_time += elapsedSeconds;
    }

    if (movingDown) {
        current_anim = CHARACTER_SHEET_WALK_DOWN_ANIM;
    } else if (movingUp) {
        current_anim = CHARACTER_SHEET_WALK_UP_ANIM;
    } else if (movingRight) {
        current_anim = CHARACTER_SHEET_WALK_RIGHT_ANIM;
    } else if (movingLeft) {
        current_anim = CHARACTER_SHEET_WALK_LEFT_ANIM;
    }

    animed = false;
    if (current_anim == -1) {
        current_anim = CHARACTER_SHEET_WALK_DOWN_ANIM;
        animed = true;
    }
    if (current_frame == -1) {
        current_frame = 0;
        animed = true;
    }

    while (frame_time > CHARACTER_FRAME_TIME) {
        frame_time -= CHARACTER_FRAME_TIME;
        current_frame = (current_frame + 1) % CHARACTER_SHEET_WALK_FRAME_COUNT;
        animed = true;
    }
}

QPainterPath Character::shape() const
{
    return shapePath;
}
