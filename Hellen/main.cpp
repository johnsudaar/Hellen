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
    log("Coucou",INFO);
    World *world = Parser::readWorld("res/PackMario/world.res");
    World *bg = Parser::readWorld("res/TestPack/world.res");

    sf::RenderWindow app(sf::VideoMode(1366, 768), "Hellen");
    sf::View* tempView = new sf::View(sf::FloatRect(533,200,100,100));

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

        app.setView(*(bg->getView()));
        bg->render(app);
        app.setView(*(world->getView()));
        world->render(app);
        app.display();
    }
    return EXIT_SUCCESS;
}
