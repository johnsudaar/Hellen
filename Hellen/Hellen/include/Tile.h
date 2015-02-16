#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "utils.h"

class Tile
{
    public:
        Tile(sf::Sprite* sprite, int x,int y);
        virtual ~Tile();
        void setPos(int x, int y);
        void render(sf::RenderWindow &window);
    protected:
    private:
        sf::Sprite* sprite;
        int x;
        int y;
};

#endif // TILE_H
