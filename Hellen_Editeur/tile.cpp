#include "tile.h"

int Tile::cur_id = 0;

Tile::Tile(int x, int y, int w, int h, QString path, QString name)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->path = path;
    QPixmap temp(path);
    this->image = temp.copy(x,y,w,h);
    this->id = Tile::cur_id++;
    if(name.compare("") == 0)
        this->name = QString::number(this->id);
}

Tile::~Tile()
{

}

QPixmap Tile::getPixmap(){
    return this->image.copy();
}

QString Tile::getName(){
    return this->name;
}
