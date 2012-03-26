#ifndef TILESCENE_H
#define TILESCENE_H

#include <QGraphicsWidget>
#include <QList>
#include <QPixmap>
#include <QString>

class TileScene : public QGraphicsWidget
{
    Q_OBJECT
public:
    TileScene(QGraphicsWidget *parent = 0);
    ~TileScene();
signals:
    
public slots:

private:
    QList<QPixmap*> tiles;

};

#endif // TILESCENE_H
