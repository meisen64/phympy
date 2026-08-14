//game.cpp
#include "game.hpp"
//#include "vec2d.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <chrono>
#include <iostream>
#include <SFML/Window.hpp>
#include <optional>

float Game::toPixels(double meters) { return static_cast<float>(meters * 50); }

double Game::toMeters(float pixels) { return static_cast<double>(pixels / 50); }

sf::Vector2f Game::toScreenPos(Vec2D pos) {
    float x = static_cast<float>(pos.x * 50);
    float y = static_cast<float>(pos.y * 50);
    return sf::Vector2f{x, 600.f - y };
}

Vec2D Game::toWorldPos(sf::Vector2i pos) {
    double x = static_cast<double>(pos.x) / 50.0;
    double y = static_cast<double>(pos.y) / 50.0;
    return Vec2D{x, 600.0/50.0 - y};
}

int Game::run(void) {

    isRunning = true;

    window.create(sf::VideoMode({800,600}), "game window");
    window.setFramerateLimit(60);

    using clock = std::chrono::high_resolution_clock;

    constexpr double FIXED_DT = 1.0 / 60.0; //60hz physics updates - 0.01667s

    constexpr double MAX_FRAME_TIME = 0.25; //250ms max accumulated time

    auto previous_time = clock::now();

    double accumulator = 0.0;

    while (isRunning && window.isOpen()) {
        auto current_time = clock::now();

        std::chrono::duration<double> frame_duration = current_time - previous_time;
        double frame_time = frame_duration.count();

        previous_time = current_time;

        if (frame_time > MAX_FRAME_TIME) { frame_time = MAX_FRAME_TIME; }
        accumulator += frame_time;

        processInput();

        //Fixed physics step consuption
        while (accumulator >= FIXED_DT) {
            _world.update(FIXED_DT);
            accumulator -= FIXED_DT;
        }

        //State interpolation
        double alpha = accumulator/FIXED_DT;
        
        render(alpha);
    }

    return 0;
}

void Game::processInput() {

    // check all the window's events that were triggered since the last iteration of the loop
    while (const std::optional event = window.pollEvent())
    {
        // "close requested" event: we close the window
        if (event->is<sf::Event::Closed>())
            window.close();

        if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            _world.add(0.5,{toWorldPos(mouseButtonPressed->position), 1.0, 0.7});
        }
    
    }

}

void Game::render(double alpha) {

    window.clear(sf::Color::Black);

    for (auto& ball : _world.getBalls()) {
        float radius = toPixels(ball.radius);
        sf::CircleShape shape(radius);
        shape.setFillColor(sf::Color(100,255,50));
        shape.setOrigin({radius,radius});
        shape.setPosition(toScreenPos(ball.physProp.pos));
        window.draw(shape);
    }

    window.display();
}