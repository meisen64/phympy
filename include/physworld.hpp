//physworld.hpp

#pragma once

#include <vector>
#include "ball.hpp"

class PhysWorld {

	std::vector<Ball> _balls;

	Vec2D _mapSize;

	double _gravity;

public:

	explicit PhysWorld(double g = -9.8, Vec2D map = Vec2D{800.0,600.0});

	const std::vector<Ball>& getBalls() const;

	void update(double);

	int size(void) const;

	void add(void);

	void add(double);

	void add(double, PhysObj);

	void removeLast(void);

	void removeAll(void);

	void setMapSize(Vec2D);

	Vec2D getMapSize() const;

	double getGravity(void) const;

	void setGravity(double);

};
