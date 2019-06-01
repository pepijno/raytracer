#include "Sphere.hpp"
#include <cmath>

SphereIntersection Sphere::intersect(Ray const ray) const {
	Vector3 const& origin = ray.getOrigin();
	Vector3 const& direction = ray.getDirection();

	Vector3 v = origin - this->origin;

	double const b = 2 * v.innerProduct(direction);
	double const c = v.innerProduct(v) - this->radius * this->radius;
	double const delta = b*b - 4 * c;

	if (delta < 1e-4) {
		return SphereIntersection(false, Vector3(0.0, 0.0, 0.0));
	}

	double const t1 = (-b - sqrt(delta))/2;
	double const t2 = (-b + sqrt(delta))/2;

	double const t = (t1 < t2) ? t1 : t2; // get the first intersection only

	return SphereIntersection(true, origin + direction * t);
}
