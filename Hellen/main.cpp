#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Parser.h"
#include "utils.h"
#include "World.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int main()
{
    World *world = Parser::readWorld("res/PackMario/world.res");
    sf::RenderWindow app(sf::VideoMode(1366, 768), "Hellen");

    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }

        app.clear();
        world->render(app);
        app.display();
    }
    return EXIT_SUCCESS;
}
