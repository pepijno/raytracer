#pragma once

#include "Object.hpp"
#include "Ray.hpp"
#include "Vector3.hpp"

class Sphere : public Object {
private:
	double radius;
public:
	Sphere(Vector3 const origin, double const radius): Object(origin), radius(radius) {};

	virtual Intersection intersect(Ray const& ray) const;
};
