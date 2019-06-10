#include "Material.hpp"
#include "Scene.hpp"

#include <random>

double const bias = 1e-4;
std::default_random_engine re;
Vector3 randomInUnitSphere() {
	std::uniform_real_distribution<double> unif(-1.0, 1.0);
	Vector3 p;
	do {
		p = Vector3(unif(re), unif(re), unif(re));
	} while (p.lengthSquared() >= 1.0);
	return p;
}


Color const Diffuse::getColor(Intersection const intersection, Scene const* scene, int8_t const depth) {
	Vector3 const hitPoint = intersection.hitPoint;
	Vector3 const normal = intersection.hitNormal;
	Vector3 const target = (normal + randomInUnitSphere()).normalized();
	Color const recursiveColor = scene->traceRay(Ray(hitPoint + target * bias, target), depth + 1);
	return this->color * recursiveColor * this->albedo;
}

Color const Metal::getColor(Intersection const intersection, Scene const* scene, int8_t const depth) {
	Vector3 const direction = intersection.ray.getDirection();
	Vector3 const hitPoint = intersection.hitPoint;
	Vector3 const normal = intersection.hitNormal;
	Vector3 const reflected = (direction - normal * 2.0 * normal.innerProduct(direction) + randomInUnitSphere() * this->fuzz).normalized();
	Color const recursiveColor = scene->traceRay(Ray(hitPoint + reflected * bias, reflected), depth + 1);
	return this->color * recursiveColor * this->albedo;
}
