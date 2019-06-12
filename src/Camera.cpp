#include "Camera.hpp"
#include <iostream>

Ray Camera::createRay(double const u, double const v) const {
	Vector3 const direction = (this->screenDL + this->horizontal * u + this->vertical * v - this->origin).normalized();
	return Ray(this->origin, direction);
}
