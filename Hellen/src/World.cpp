#include "World.h"

World::World(map<int,sf::Texture*> *textures, vector<Tile*> *tiles)
{
    this->_textures = textures;
    this->tiles = tiles;
    this->view = new sf::View(sf::FloatRect(0,0,200,200));
    this->s_x = 100;
    this->s_y = 100;
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
    this->s_x = x;
    this->s_y = y;
}

void World::move(int x, int y){
    this->scrollTo(this->s_x + x, this->s_y + y);
}

void World::zoom(float factor){
    this->size += factor;
    cout<<this->size<<endl;
    this->view->setSize(this->size, this->size);
}
