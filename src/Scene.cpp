#include "Scene.hpp"

#include <fstream>
#include <limits>
#include <random>

#include <iostream>

void Scene::addObject(Object* object) {
	this->objects.emplace_back(std::move(object));
}

std::default_random_engine re;

Vector3 randomInUnitSphere() {
	std::uniform_real_distribution<double> unif(-1.0, 1.0);
	Vector3 p;
	do {
		p = Vector3(unif(re), unif(re), unif(re));
	} while (p.lengthSquared() >= 1.0);
	return p;
}

int8_t const MAX_DEPTH = 5;

Color Scene::traceRay(Ray const& ray, int8_t const depth) const {
	Color color = WHITE;
	if (depth >= MAX_DEPTH) {
		return color;
	}
	double maxT = std::numeric_limits<double>::max();
	Object* object = nullptr;
	Intersection intersection(false);
	for (auto const& ptr : this->objects) {
		Intersection i = ptr.get()->intersect(ray);
		if (i.isIntersect) {
			if (i.t < maxT) {
				maxT = intersection.t;
				object = ptr.get();
				intersection = i;
			}
		}
	}
	double const bias = 1e-4;
	if (object) {
		Color surfaceColor = BLACK;
		Vector3 const hitPoint = intersection.hitPoint;
		Vector3 const normal = intersection.hitNormal;
		Vector3 const target = (normal + randomInUnitSphere()).normalized();
		Color recursiveColor = this->traceRay(Ray(hitPoint + target * bias, target), depth + 1);
		color = object->getColor(hitPoint) * recursiveColor * 0.8;
	}
	return color;
}

void Scene::createImage(std::string const fileName) const {
	int height = 400;
	int width = 400;
	int samplingAmount = 1000;
	const char* imageFileName = fileName.c_str();

	std::ofstream ofs(imageFileName, std::ios::out | std::ios::binary);

	ofs << "P6\n" << width << " " << height << "\n255\n";

	std::uniform_real_distribution<double> u(-0.5, 0.5);
	for(int i = 0; i < height; ++i) {
		for(int j = 0; j < width; ++j) {
			Color color = BLACK;
			for(int s = 0; s < samplingAmount; ++s) {
				double const dw = u(re);
				double const dh = u(re);
				Ray ray = this->camera.createRay(i, j, (double)(width + dw), (double)(height + dh));
				color = color + this->traceRay(ray, 0);
			}
			color = color / samplingAmount;

			ofs << (unsigned char)(255 * std::min(1.0, std::max(0.0, color.R)))
				<< (unsigned char)(255 * std::min(1.0, std::max(0.0, color.G)))
				<< (unsigned char)(255 * std::min(1.0, std::max(0.0, color.B)));
		}
	}

	ofs.close();
}
