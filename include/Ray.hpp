#pragma once

#include "Vector3.hpp"

class Ray {
private:
	Vector3 origin;
	Vector3 direction;
public:
	Ray(Vector3 const o, Vector3 const d): origin(o), direction(d) {};
	Vector3 const& getOrigin() const { return this->origin; };
	Vector3 const& getDirection() const { return this->direction; };
};
