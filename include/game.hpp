//game.hpp
#pragma once

#include "physworld.hpp"
#include <SFML/Graphics.hpp>

class Game {

    PhysWorld _world;

    bool isRunning;

    sf::RenderWindow window;

public:

    int run(void);

    void processInput();

    void render(double);

};