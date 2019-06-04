#include "Camera.hpp"
#include <iostream>

Ray Camera::createRay(double const widthN, double const heightN, double const maxWidth, double const maxHeight) const {
	double const widthFactor = widthN/maxWidth;
	double const heightFactor = heightN/maxHeight;

	Vector3 diffWidth = this->screenUR - this->screenUL;
	Vector3 diffHeight = this->screenDL - this->screenUL;

	Vector3 dirFromZero = this->screenUL + diffWidth * widthFactor + diffHeight * heightFactor;
	Vector3 direction = dirFromZero - this->origin;

	return Ray(this->origin, direction.normalized());
}
