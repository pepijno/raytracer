#pragma once

#include "Vector3.hpp"
#include "Ray.hpp"

struct Intersection {
	bool isIntersect;
	double t;

	Intersection(bool isIntersect, double t): isIntersect(isIntersect), t(t) {};
};

class Object {
protected:
	Vector3 origin;
public:
	Object(Vector3 const origin): origin(origin) {};
	virtual Intersection intersect(Ray const& ray) const = 0;
};
