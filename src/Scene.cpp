#include "Scene.hpp"

#include <fstream>
#include <limits>
#include <random>

#include <iostream>

void Scene::addObject(Object* object) {
	this->objects.emplace_back(std::move(object));
}

int8_t const MAX_DEPTH = 5;

Color Scene::traceRay(Ray const& ray, int8_t const depth) const {
	if (depth >= MAX_DEPTH) {
		return BLACK;
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
	if (object) {
		return object->getColor(intersection, this, depth);
	}
	return WHITE;
}

void Scene::createImage(std::string const fileName) const {
	int height = 400;
	int width = 400;
	int samplingAmount = 1000;
	const char* imageFileName = fileName.c_str();

	std::ofstream ofs(imageFileName, std::ios::out | std::ios::binary);

	ofs << "P6\n" << width << " " << height << "\n255\n";

	std::uniform_real_distribution<double> u(-0.5, 0.5);
	std::default_random_engine re;
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
