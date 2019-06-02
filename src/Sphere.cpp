#include "Sphere.hpp"
#include <cmath>
#include <iostream>

Intersection Sphere::intersect(Ray const& ray) const {
	Vector3 const& origin = ray.getOrigin();
	Vector3 const& direction = ray.getDirection();

	Vector3 v = origin - this->origin;

	double const a = direction.lengthSquared();
	double const b = 2 * v.innerProduct(direction);
	double const c = v.innerProduct(v) - this->radius * this->radius;
	double const delta = b*b - 4 * a * c;

	if (delta < 1e-4) {
		return Intersection(false, 0.0);
	}

	double const t1 = (-b - sqrt(delta))/(a * 2);
	double const t2 = (-b + sqrt(delta))/(a * 2);

	double const t = (t1 < t2) ? t1 : t2; // get the first intersection only

	return Intersection(true, t);
}
