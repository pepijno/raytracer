#include "Camera.hpp"

Ray Camera::createRay(uint32_t widthN, uint32_t heightN, uint32_t maxWidth, uint32_t maxHeight) const {
	double const widthFactor = ((double) widthN)/maxWidth;
	double const heightFactor = ((double) heightN)/maxHeight;

	Vector3 diffWidth = this->screenUR - this->screenUL;
	Vector3 diffHeight = this->screenDL - this->screenUL;

	Vector3 dirFromZero = this->screenUL + diffWidth * widthFactor + diffHeight * heightFactor;
	Vector3 direction = this->origin - dirFromZero;

	return Ray(this->origin, direction);
};
