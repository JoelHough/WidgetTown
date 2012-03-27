#ifndef CHARACTERVIEW_H
#define CHARACTERVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>

class CharacterView : public QGraphicsView
{
    Q_OBJECT
public:
    CharacterView(QGraphicsScene *scene, QWidget *parent = 0);

public slots:
    void tick();
};

#endif // CHARACTERVIEW_H
