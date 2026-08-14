//vec2d.hpp

#pragma once

#include <cmath>

struct Vec2D {

	double x;
	
	double y;

	Vec2D() : x(0.0), y(0.0) {}

	//Vec2D(const Vec2D& vec) : x(vec.x), y(vec.y) {}

	Vec2D(double a, double b) : x(a), y(b) {}

	void zero() { x = y = 0.0; }

	double length() const { return std::sqrt(x * x + y * y); }
	
	double lengthSqr() const { return x * x + y * y; }

	Vec2D unit() const {

		Vec2D unit;
		double len = length();

		if (len > 1e-6) {		//1e-6 (epsilon syntax) = 0.000001
			unit.x = x / len;
			unit.y = y / len;
		}

		return unit;
	
	}

	double dot(const Vec2D& vec) const { return x * vec.x + y * vec.y; }

	double cross(const Vec2D& vec) const { return x * vec.y - y * vec.x; }
/*
	Vec2D& operator=(const Vec2D& vec) {
		x = vec.x;
        	y = vec.y;
	        return *this;
	}
*/
	Vec2D& operator+=(const Vec2D& vec) {
		x += vec.x;
		y += vec.y;
		return *this;
	}

	Vec2D& operator-=(const Vec2D& vec) {
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	Vec2D& operator*=(double scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Vec2D operator+(const Vec2D& vec) const {
		Vec2D result = *this;
		result += vec;
		return result;
	}

	Vec2D operator-(const Vec2D& vec) const {
		Vec2D result = *this;
		result -= vec;
		return result;
	}

	Vec2D operator*(double scalar) const {
		Vec2D result = *this;
		result *= scalar;
		return result;
	}

};

	inline Vec2D operator*(double scalar, const Vec2D& vec) {
		return vec * scalar;
	}
