#pragma once

#include "Object.hpp"
#include "Ray.hpp"
#include "Vector3.hpp"

class Sphere : public Object {
private:
	double radius;
public:
	Sphere(Vector3 const o, Material* m, double const r): Object(o, m), radius(r) {};

	virtual Intersection intersect(Ray const& ray) const;
};
