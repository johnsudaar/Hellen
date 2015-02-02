#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "utils.h"
#include "Tile.h"

class World
{
    public:
        World(map<int,sf::Texture*>* textures, vector<Tile*>* tiles);
        virtual ~World();
        void render(sf::RenderWindow &window);
    protected:
    private:
        map<int,sf::Texture*>* _textures;
        vector<Tile*>* tiles;
};

#endif // WORLD_H
