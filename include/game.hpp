//game.hpp
#pragma once

#include "physworld.hpp"
#include <SFML/Graphics.hpp>

class Game {

    PhysWorld _world;

    bool isRunning;

    sf::RenderWindow window;

    float toPixels(double);

    double toMeters(float);

    sf::Vector2f toScreenPos(Vec2D);

    Vec2D toWorldPos(sf::Vector2i);

public:

    int run(void);

    void processInput();

    void render(double);

};