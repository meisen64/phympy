#include "physworld.hpp"
#include "vec2d.hpp"

PhysWorld::PhysWorld(double g, Vec2D v) : _gravity(g), _mapSize(v) {}

const std::vector<Ball>& PhysWorld::getBalls(void) const { return _balls; }

void PhysWorld::update(double dt) {

	const double floor = 600;

	for (auto& ball : _balls) {

		ball.physProp.vel += Vec2D{0,_gravity} * dt;
		ball.physProp.pos += ball.physProp.vel * dt;
		
		//Check floor collision
		double bottomEdge = ball.physProp.pos.y + ball.radius;
		if (bottomEdge >= floor) {
			ball.physProp.pos.y = floor - ball.radius;
			if (ball.physProp.vel.y > 0.0) {
				ball.physProp.vel.y *= -ball.physProp.bounce;
			}
		}
		//End floor collision
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
