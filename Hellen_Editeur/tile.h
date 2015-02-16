#ifndef TILE_H
#define TILE_H

#include <QString>
#include <QPixmap>
#include <QDebug>
#include <QObject>

class Tile
{
public:
    Tile(int x, int y, int w, int h, QString path, QString name);
    ~Tile();
    QPixmap getPixmap();
    QString getName();
private:
    static int cur_id;
    int x,y,w,h,id;
    QString path;
    QPixmap image;
    QString name;
};

#endif // TILE_H
