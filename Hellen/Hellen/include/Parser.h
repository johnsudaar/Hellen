//#ifndef PARSER_H
//#define PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <SFML/Graphics.hpp>

#include "Tile.h"
#include "World.h"
#include "utils.h"

class Parser
{
    public:
        Parser();
        virtual ~Parser();
        static World* readWorld(string file);
    protected:
    private:
        static string getPath(string file);
        static map<int,sf::Texture*> *getTexture(string line,string file, map<int,sf::Texture*> *textures);
        static Tile* getTile(string line, string file, ifstream &descFile, map<int,sf::Texture*> *textures);
        static sf::Sprite* readSprite(string file, map<int,sf::Texture*> *textures);
};

//#endif // PARSER_H
