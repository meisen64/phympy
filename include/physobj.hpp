//physobj.hpp

#pragma once

#include "vec2d.hpp"

struct PhysObj {

	Vec2D pos;
	Vec2D vel;
	Vec2D nForce; //Net force

	double iMass;  //Inverse mass - Optimized for performance (1 / mass)
	double bounce; //Bounciness - Coeff of restitution (0.0 = clay, 1.0 = perfect bounce)

	//Ang2D ang;

	PhysObj() : iMass(1), bounce(0.7) {}

	PhysObj(Vec2D p, double m, double b) : pos(p), bounce(b) {
		if(m > 0.0) { iMass = 1.0 / m; }
		else { iMass = 0.0; }	//Static, unmovable object
	}

//	PhysObj(const PhysObj& obj) : pos(obj.pos), vel(obj.vel), nForce(obj.nForce),iMass(obj.iMass), bounce(obj.bounce) {}
	
	double mass() const { 
		double result = 0;
		if (iMass > 0.0) { result = 1 / iMass; }
		return result;
	}
};