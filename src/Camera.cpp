#include "Camera.hpp"
#include <iostream>
#include <random>

std::default_random_engine ra;
Vector3 randomInUnitDisk() {
	std::uniform_real_distribution<double> unif(-1.0, 1.0);
	Vector3 p;
	do {
		p = Vector3(unif(ra), unif(ra), 0);
	} while (p.lengthSquared() >= 1.0);
	return p;
}

Ray Camera::createRay(double const s, double const t) const {
	Vector3 rd = randomInUnitDisk() * this->lensRadius;
	Vector3 offset = this->u * rd.getX() + this->v * rd.getY();
	Vector3 const direction = (this->screenDL + this->horizontal * s + this->vertical * t - this->origin - offset).normalized();
	return Ray(this->origin + offset, direction);
}
