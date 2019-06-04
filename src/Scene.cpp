#include "Bmp.hpp"
#include "Scene.hpp"

#include <iostream>
#include <limits>
#include <random>

void Scene::addObject(Object* object) {
	this->objects.emplace_back(std::move(object));
}

void Scene::addLight(Vector3 source) {
	this->lights.push_back(source);
}

Color Scene::traceRay(Ray const& ray) const {
	Color color = BLACK;
	double maxT = std::numeric_limits<double>::max();
	Object* object = nullptr;
	for (auto const& ptr : this->objects) {
		Intersection intersection = ptr.get()->intersect(ray);
		if (intersection.isIntersect) {
			if (intersection.t < maxT) {
				maxT = intersection.t;
				object = ptr.get();
			}
		}
	}
	double const bias = 1e-4;
	if (object) {
		Color surfaceColor = BLACK;
		Vector3 const hitPoint = ray.getOrigin() + ray.getDirection() * maxT;
		Vector3 const normal = (hitPoint - object->getOrigin()).normalized();
		for (auto const& light : this->lights) {
			double transmission = 1.0;
			Vector3 const lightDirection = (light - hitPoint).normalized();
			for (auto const& ptr : this->objects) {
				auto const r = Ray(hitPoint + normal * bias, lightDirection);
				Intersection intersection = ptr.get()->intersect(r);
				if (intersection.isIntersect) {
					transmission = 0.0;
					break;
				}
			}
			surfaceColor = surfaceColor + object->getColor() * transmission * std::max(0.0, normal.innerProduct(lightDirection));
		}
		color = surfaceColor;
	}
	return color;
}

void Scene::createImage(std::string const fileName) const {
	int height = 400;
	int width = 400;
	int samplingAmount = 100;
	unsigned char image[height][width][bytesPerPixel];
	const char* imageFileName = fileName.c_str();

	int i, j, s;
	std::uniform_real_distribution<double> unif(-0.5, 0.5);
	std::default_random_engine re;
	for(i=0; i<height; i++){
		for(j=0; j<width; j++){
			Color color = BLACK;
			for(s = 0; s < samplingAmount; ++s) {
				double const dw = unif(re);
				double const dh = unif(re);
				Ray ray = this->camera.createRay(i, j, (double)(width + dw), (double)(height + dh));
				color = color + this->traceRay(ray);
			}
			color = color / samplingAmount;
			image[i][j][2] = (unsigned char)(color.R); ///red
			image[i][j][1] = (unsigned char)(color.G); ///green
			image[i][j][0] = (unsigned char)(color.B); ///blue
		}
	}

	generateBitmapImage((unsigned char *)image, height, width, imageFileName);
}
