#include "Sphere.hpp"
#include <cmath>
#include <iostream>

Intersection Sphere::intersect(Ray const& ray) const {
	Vector3 const& rayOrigin = ray.getOrigin();
	Vector3 const& direction = ray.getDirection();

	Vector3 const v = this->origin - rayOrigin;

	double const tca = v.innerProduct(direction);
	if (tca < 0) {
		return Intersection(false, 0.0);
	}
	
	double const d2 = v.innerProduct(v) - tca * tca;
	if (d2 > this->radius * this->radius) {
		return Intersection(false, 0.0);
	}

	double const thc = sqrt(radius * radius - d2);
	if (tca - thc < 0) {
		return Intersection(true, tca + thc);
	}
	return Intersection(true, tca - thc);
}
