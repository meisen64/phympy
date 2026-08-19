//game.cpp
#include "game.hpp"
#include "vec2d.hpp"
//#include "vec2d.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <chrono>
#include <iostream>
#include <SFML/Window.hpp>
#include <optional>

Game::Game(sf::Vector2u ws) : windowSize(ws) {}

float Game::toPixels(double meters) { return static_cast<float>(meters * PPM); }

double Game::toMeters(float pixels) { return static_cast<double>(pixels / PPM); }

sf::Vector2f Game::toScreenPos(Vec2D pos) {
    float x = static_cast<float>(pos.x * PPM);
    float y = static_cast<float>(pos.y * PPM);
    return sf::Vector2f{x, static_cast<float>(windowSize.y) - y };
}

Vec2D Game::toWorldPos(sf::Vector2i pos) {
    double x = static_cast<double>(pos.x) / PPM;
    double y = static_cast<double>(pos.y) / PPM;
    return Vec2D{x, static_cast<double>(windowSize.y)/PPM - y};
}

int Game::run(void) {

    isRunning = true;

    world.setMapSize({toMeters(windowSize.x), toMeters(windowSize.y)});

    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    window.create(sf::VideoMode(windowSize), "game window", sf::Style::Default, sf::State::Windowed, settings);
    window.setFramerateLimit(60);

    using clock = std::chrono::high_resolution_clock;

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
            world.update(FIXED_DT);
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
            world.add(0.5,{toWorldPos(mouseButtonPressed->position), 1.0, 0.7});
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Z && keyPressed->control) {
                world.removeLast();
            }
        }
    
    }

}

void Game::render(double alpha) {

    window.clear(sf::Color::Black);

    for (auto& ball : world.getBalls()) {
        float radius = toPixels(ball.radius);
        sf::CircleShape shape(radius);
        shape.setFillColor(sf::Color(100,255,50));
        shape.setOrigin({radius,radius});
        shape.setPosition(toScreenPos(ball.physProp.pos));
        window.draw(shape);
    }

    window.display();
}