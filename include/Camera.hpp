#pragma once

#include <cstdint>
#include <cmath>

#include "Vector3.hpp"
#include "Ray.hpp"

constexpr double pi() {
	return std::atan(1) * 4;
}

class Camera {
private:
	Vector3 origin;
	Vector3 screenDL;
	Vector3 horizontal;
	Vector3 vertical;
	Vector3 u, v, w;
	double lensRadius;
public:
	Camera(Vector3 const lookFrom, Vector3 const lookAt, Vector3 const vup, double const vofv, double const aspect, double const aperture, double const focusDistance) {
		this->lensRadius = aperture / 2.0;
		double const theta = vofv * pi() / 180;
		double const halfHeight = std::tan(theta / 2);
		double const halfWidth = aspect * halfHeight;
		this->w = (lookFrom - lookAt).normalized();
		this->u = vup.outerProduct(w).normalized();
		this->v = this->w.outerProduct(u);
		this->origin = lookFrom;
		this->screenDL = this->origin - this->u * halfWidth * focusDistance - this->v * halfHeight * focusDistance - this->w * focusDistance;
		this->horizontal = u * 2 * halfWidth * focusDistance;
		this->vertical = v * 2 * halfHeight * focusDistance;
	};

	Ray createRay(double const s, double const t) const;
};
