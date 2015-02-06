#include "World.h"

World::World(map<int,sf::Texture*> *textures, vector<Tile*> *tiles)
{
    this->_textures = textures;
    this->tiles = tiles;
    this->view = new sf::View(sf::FloatRect(0,0,533,300));
    this->p_x = 100;
    this->p_y = 100;
    this->size = 200.0;
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

sf::View* World::getView(){
    return this->view;
}

void World::scrollTo(int x, int y){
    this->view->setCenter((float)x,(float)y);
    this->p_x = x;
    this->p_y = y;
}

void World::move(int x, int y){
    this->scrollTo(this->p_x + x, this->p_y + y);
}

void World::zoom(float factor){
    this->size += factor;
    this->view->setSize(this->size, this->size);
}
