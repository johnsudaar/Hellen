#include "World.h"

World::World(map<int,sf::Texture*> *textures, vector<Tile*> *tiles)
{
    this->_textures = textures;
    this->tiles = tiles;
}

World::~World()
{
    //dtor
}

void World::render(sf::RenderWindow &window){
    for(std::vector<Tile*>::iterator it = this->tiles->begin(); it != this->tiles->end(); ++it){
        (*it)->render(window);
    }
}
