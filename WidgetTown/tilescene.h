#ifndef TILESCENE_H
#define TILESCENE_H

#include <QGraphicsWidget>
#include <QList>
#include <QPixmap>
#include <QString>

class TileMapWidget : public QGraphicsWidget
{
    Q_OBJECT
public:
    TileMapWidget(QGraphicsWidget *parent = 0);
    ~TileMapWidget();

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

signals:
    
public slots:
    void tick();

private:
    QList<QPixmap*> tiles;

};

#endif // TILESCENE_H
