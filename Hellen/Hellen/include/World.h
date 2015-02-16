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
        sf::View* getView();
        void scrollTo(int x, int y);
        void move(int x, int y);
        void zoom(float factor);
    protected:
    private:
        int p_x, p_y;
        float size;
        map<int,sf::Texture*>* _textures;
        vector<Tile*>* tiles;
        sf::View* view;
};

#endif // WORLD_H
