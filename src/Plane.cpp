#include "Plane.hpp"

#include <iostream>

Intersection Plane::intersect(Ray const& ray) const {
	double const d = this->normal.innerProduct(ray.getDirection());
	if (std::abs(d) < 1e-4) {
		return Intersection(false);
	}

	Vector3 const pl = this->origin - ray.getOrigin();
	double const t = pl.innerProduct(this->normal) / d;

	if (t < 1e-4) {
		return Intersection(false);
	}

	Vector3 const hitPoint = ray.getOrigin() + ray.getDirection() * t;
	Vector3 const hitNormal = (d < 0 ? this->normal : this->normal * -1);
	return Intersection(true, t, hitPoint, hitNormal);
}
