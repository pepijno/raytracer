#include "Bmp.hpp"
#include "Scene.hpp"

#include <iostream>

void Scene::addObject(Object* object) {
	this->objects.emplace_back(std::move(object));
}

Color Scene::traceRay(Ray const& ray) const {
	for (auto const& ptr : this->objects) {
		Intersection intersection = ptr.get()->intersect(ray);
		if (intersection.isIntersect) {
			return Color(255, 0, 0);
		}
	}
	return Color(0, 0, 0);
}

void Scene::createImage(std::string const fileName) const {
	int height = 400;
	int width = 400;
	unsigned char image[height][width][bytesPerPixel];
	const char* imageFileName = fileName.c_str();

	int i, j;
	for(i=0; i<height; i++){
		for(j=0; j<width; j++){
			Ray ray = this->camera.createRay(i, j, width, height);
			Color color = this->traceRay(ray);
			image[i][j][2] = (unsigned char)(color.R); ///red
			image[i][j][1] = (unsigned char)(color.G); ///green
			image[i][j][0] = (unsigned char)(color.B); ///blue
		}
	}

	generateBitmapImage((unsigned char *)image, height, width, imageFileName);
}
