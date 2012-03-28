#ifndef NPC_H
#define NPC_H

#include "character.h"

#include <QObject>
#include <QTimer>

class NPC : public QObject, public Character
{
    Q_OBJECT
public:
    NPC(QString charsheet, QGraphicsItem *parent = 0);

public slots:
    void push();

protected:
    virtual void oof();
    void moveDirection();
    int direction;
    qreal duration;
    QTimer moveTimer;
};

#endif // NPC_H
