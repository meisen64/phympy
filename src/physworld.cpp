#include "physworld.hpp"
#include "ball.hpp"
#include "vec2d.hpp"
#include <cstddef>
#include <iostream>

PhysWorld::PhysWorld(double g, Vec2D v) : _gravity(g), _mapSize(v) {}

const std::vector<Ball>& PhysWorld::getBalls(void) const { return _balls; }

void PhysWorld::update(double dt) {

	for (size_t i = 0; i < _balls.size(); i++) {

		Ball& ball = _balls.at(i);

		ball.physProp.vel += Vec2D{0,_gravity} * dt;
		ball.physProp.pos += ball.physProp.vel * dt;
		
		//Check map edge collision
		if (ball.physProp.pos.x <= ball.radius) {
			ball.physProp.pos.x = ball.radius;
			if (ball.physProp.vel.x < 0.0) {
				ball.physProp.vel.x *= -ball.physProp.bounce;
			}
		}
		if (ball.physProp.pos.x >= _mapSize.x - ball.radius) {
			ball.physProp.pos.x = _mapSize.x - ball.radius;
			if (ball.physProp.vel.x > 0.0) {
				ball.physProp.vel.x *= -ball.physProp.bounce;
			}
		}
		if (ball.physProp.pos.y <= ball.radius) {
			ball.physProp.pos.y = ball.radius;
			if (ball.physProp.vel.y < 0.0) {
				ball.physProp.vel.y *= -ball.physProp.bounce;
			}
		}
		if (ball.physProp.pos.y >= _mapSize.y - ball.radius) {
			ball.physProp.pos.y = _mapSize.y - ball.radius;
			if (ball.physProp.vel.y > 0.0) {
				ball.physProp.vel.y *= -ball.physProp.bounce;
			}
		}
		//End map edge collision

		//Collision detection
		for (size_t j = i + 1; j < _balls.size(); j++) {
			Ball& ball2 = _balls.at(j);
			
			if ((ball2.physProp.pos - ball.physProp.pos).length() < (ball2.radius + ball.radius)) {
				//Initial object separation
				Vec2D posA = ball.physProp.pos;
				Vec2D posB = ball2.physProp.pos;
				Vec2D collisionVec = (posB - posA).unit();
				double overlap = (ball.radius + ball2.radius) - (posB - posA).length();
				ball.physProp.pos -= collisionVec * (overlap / 2);
				ball2.physProp.pos += collisionVec * (overlap / 2); 

			}
		}
	}
}

int PhysWorld::size(void) const { return _balls.size(); }

void PhysWorld::add(void) { _balls.emplace_back(); }

void PhysWorld::add(double r) { _balls.emplace_back(r); }

void PhysWorld::add(double r, PhysObj p) { _balls.emplace_back(r,p); }

void PhysWorld::removeLast(void) { 

	if(!_balls.empty()) {
		_balls.pop_back(); 
	}

}

void PhysWorld::removeAll(void) { _balls.clear(); }

void PhysWorld::setMapSize(Vec2D map) { _mapSize = map; }

Vec2D PhysWorld::getMapSize() const { return _mapSize; }

double PhysWorld::getGravity(void) const { return _gravity; }

void PhysWorld::setGravity(double g) {
	_gravity = g;
}
