#pragma once

#include "Vector3.hpp"
#include "Ray.hpp"

struct Intersection {
	bool isIntersect;
	Vector3 intersection;

	Intersection(bool isIntersect, Vector3 const intersection): isIntersect(isIntersect), intersection(intersection) {};
};

class Object {
protected:
	Vector3 origin;
public:
	Object(Vector3 const origin): origin(origin) {};
	virtual Intersection intersect(Ray const& ray) const = 0;
};
