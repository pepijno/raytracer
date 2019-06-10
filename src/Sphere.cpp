#include "Sphere.hpp"
#include <cmath>
#include <iostream>

Intersection Sphere::intersect(Ray const& ray) const {
	Vector3 const& rayOrigin = ray.getOrigin();
	Vector3 const& direction = ray.getDirection();

	Vector3 const v = this->origin - rayOrigin;

	double const tca = v.innerProduct(direction);
	if (tca < 0) {
		return Intersection(false);
	}
	
	double const d2 = v.innerProduct(v) - tca * tca;
	if (d2 > this->radius * this->radius) {
		return Intersection(false);
	}

	double const thc = sqrt(radius * radius - d2);
	if (tca - thc < 0) {
		double const t = tca + thc;
		Vector3 const hitPoint = rayOrigin + direction * t;
		Vector3 const normal = (hitPoint - this->getOrigin()).normalized();
		return Intersection(true, t, hitPoint, normal, ray);
	}
	double const t = tca - thc;
	Vector3 const hitPoint = rayOrigin + direction * t;
	Vector3 const normal = (hitPoint - this->getOrigin()).normalized();
	return Intersection(true, t, hitPoint, normal, ray);
}
