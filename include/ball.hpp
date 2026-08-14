//ball.hpp

#pragma once

#include "physobj.hpp"

struct Ball {

	PhysObj physProp;

	double radius; 

	explicit Ball(double r = 5) : radius(r) {}

	Ball(double r, PhysObj p) : radius(r), physProp(p) {}
};
