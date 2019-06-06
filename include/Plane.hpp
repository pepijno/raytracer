#pragma once 

#include "Object.hpp"
#include "Vector3.hpp"

class Plane : public Object {
private:
	Vector3 normal;
public:
	Plane(Vector3 const o, Color const c, Vector3 const n) : Object(o, c), normal(n) {};

	Intersection intersect(Ray const& ray) const;
};
