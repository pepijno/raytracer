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
	Camera(Vector3 const o, Vector3 const sUL, Vector3 const sUR, Vector3 const sDL):
			origin(o), screenUL(sUL), screenUR(sUR), screenDL(sDL) {};

	Ray createRay(double const widthN, double const heightN, double const maxWidth, double const maxHeight) const;
};
