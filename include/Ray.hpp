#pragma once

#include "Vector3.hpp"

class Ray {
private:
	Vector3 origin;
	Vector3 direction;
public:
	Ray(Vector3 const origin, Vector3 const direction): origin(origin), direction(direction) {};
	Vector3 const& getOrigin() const { return this->origin; };
	Vector3 const& getDirection() const { return this->direction; };
};
