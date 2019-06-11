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

Color const Dielectric::getColor(Intersection const intersection, Scene const* scene, int8_t const depth) {
	Vector3 const direction = intersection.ray.getDirection();
	Vector3 const hitPoint = intersection.hitPoint;
	Vector3 normal = intersection.hitNormal;
	Vector3 const reflected = (direction - normal * 2.0 * normal.innerProduct(direction)).normalized();
	double cosi = direction.innerProduct(normal);
	double etai = 1;
	double etat = this->refractionIndex;
	if (cosi < 0) {
		cosi = -cosi;
	} else {
		std::swap(etai, etat);
		normal = normal * -1;
	}
	double const eta = etai / etat;
	double const sint = eta * std::sqrt(std::max(0.0, 1 - cosi * cosi));
	double const k = 1 - eta * eta * (1 - cosi * cosi);

	double kr = 1;
	if (sint < 1) {
		double const cost = std::sqrt(std::max(0.0, 1 - sint * sint));
		cosi = std::abs(cosi);
		double const Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
		double const Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
		kr = (Rs * Rs + Rp * Rp) / 2;
	}

	Vector3 const rayDirection = (direction * eta + normal * (eta * cosi - std::sqrt(k))).normalized();
	Color refractColor = BLACK;
	if (kr != 1) {
		refractColor = scene->traceRay(Ray(hitPoint + rayDirection * bias, rayDirection), depth + 1);
	}
	Color reflectColor = scene->traceRay(Ray(hitPoint + reflected * bias, reflected), depth + 1);
	return reflectColor * kr + refractColor * (1 - kr);
}
