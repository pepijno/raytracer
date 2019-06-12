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
public:
	Camera(Vector3 const lookFrom, Vector3 const lookAt, Vector3 const vup, double const vofv, double const aspect) {
		double const theta = vofv * pi() / 180;
		double const halfHeight = std::tan(theta / 2);
		double const halfWidth = aspect * halfHeight;
		Vector3 const w = (lookFrom - lookAt).normalized();
		Vector3 const u = vup.outerProduct(w).normalized();
		Vector3 const v = w.outerProduct(u);
		this->origin = lookFrom;
		this->screenDL = this->origin - u * halfWidth - v * halfHeight - w;
		this->horizontal = u * 2 * halfWidth;
		this->vertical = v * 2 * halfHeight;
	};

	Ray createRay(double const maxWidth, double const maxHeight) const;
};
