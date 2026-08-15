//game.hpp
#pragma once

#include "physworld.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Game {

    static constexpr double FIXED_DT = 1.0 / 60.0; //60hz physics updates - 0.01667s
    static constexpr double MAX_FRAME_TIME = 0.25; //250ms max accumulated time
    static constexpr double PPM = 50.0;   //Pixels per Meter

    bool isRunning;

    PhysWorld world;

    sf::Vector2u windowSize;
    sf::RenderWindow window;

    float toPixels(double);
    double toMeters(float);
    sf::Vector2f toScreenPos(Vec2D);
    Vec2D toWorldPos(sf::Vector2i);

public:

    explicit Game(sf::Vector2u ws = sf::Vector2u{1200,900});

    int run(void);

    void processInput();

    void render(double);

};