#include "Tile.h"

Tile::Tile(sf::Sprite* sprite, int x, int y)
{
    this->sprite = sprite;
    this->setPos(x,y);
}

Tile::~Tile()
{
    //dtor
}
void Tile::setPos(int x, int y){
    if(x >= 0 && y >=0){
        this->sprite->move((float) x, (float) y);
    }else
        log("Invalid Position !",ERROR);
}

void Tile::render(sf::RenderWindow &window){
    window.draw(*(this->sprite));
}
