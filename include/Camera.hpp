#pragma once

#include <cstdint>

#include "Vector3.hpp"
#include "Ray.hpp"

class Camera {
private:
	Vector3 origin;
	Vector3 screenUL;
	Vector3 screenUR;
	Vector3 screenDL;
public:
	Camera(Vector3 const origin, Vector3 const screenUL, Vector3 const screenUR, Vector3 const screenDL):
			origin(origin), screenUL(screenUL), screenUR(screenUR), screenDL(screenDL) {};

	Ray createRay(uint32_t widthN, uint32_t heightN, uint32_t maxWidth, uint32_t maxHeight) const;
};
