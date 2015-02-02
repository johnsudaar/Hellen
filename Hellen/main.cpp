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
    sf::View* tempView = new sf::View(sf::FloatRect(200,200,100,100));
    app.setView(*tempView);

    app.setView(*(world->getView()));
    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            world->move(1,0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            world->move(-1,0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            world->zoom(1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            world->zoom(-1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            app.close();
        }
        app.clear();
        world->render(app);
        app.setView(*(world->getView()));
        app.display();
    }
    return EXIT_SUCCESS;
}
