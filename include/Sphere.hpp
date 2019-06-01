#pragma once

#include "Object.hpp"
#include "Ray.hpp"
#include "Vector3.hpp"

struct SphereIntersection {
	bool isIntersect;
	Vector3 intersection;

	SphereIntersection(bool isIntersect, Vector3 const intersection): isIntersect(isIntersect), intersection(intersection) {};
};

class Sphere : Object {
private:
	double radius;
public:
	Sphere(Vector3 const origin, double const radius): Object(origin), radius(radius) {};
	SphereIntersection intersect(Ray const ray) const;
};
