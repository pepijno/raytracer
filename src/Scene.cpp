#include "Scene.hpp"

#include <fstream>
#include <limits>
#include <random>

#include <iostream>

#include <taskflow/taskflow.hpp>

void Scene::addObject(Object* object) {
	this->objects.emplace_back(std::move(object));
}

int8_t const MAX_DEPTH = 5;

Color Scene::traceRay(Ray const& ray, int8_t const depth) const {
	if (depth >= MAX_DEPTH) {
		return BLACK;
	}
	double minT = std::numeric_limits<double>::max();
	Object* object = nullptr;
	Intersection intersection(false);
	for (auto const& ptr : this->objects) {
		Intersection i = ptr.get()->intersect(ray);
		if (i.isIntersect) {
			if (i.t < minT) {
				minT = i.t;
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

void Scene::createImage(std::string const fileName, size_t const numThreads) const {
	size_t const height = 1600;
	size_t const width = 1600;
	int samplingAmount = 1000;
	const char* imageFileName = fileName.c_str();

	std::ofstream ofs(imageFileName, std::ios::out | std::ios::binary);

	ofs << "P6\n" << width << " " << height << "\n255\n";

	std::vector<std::vector<Color>> colors(height, std::vector<Color>(width));

	std::uniform_real_distribution<double> u(-0.5, 0.5);
	std::default_random_engine re;
	auto func = [&](size_t const from, size_t const to) {
		for(size_t i = 0; i < height; ++i) {
			if (((i + 1) % 100) == 0) {
				std::cout << i << "\n";
			}
			for(size_t j = from; j < to; ++j) {
				Color color = BLACK;
				for(int s = 0; s < samplingAmount; ++s) {
					double const dw = u(re);
					double const dh = u(re);
					double const x = static_cast<double>(j + dw) / width;
					double const y = static_cast<double>(i + dh) / height;
					Ray ray = this->camera.createRay(x, y);
					color = color + this->traceRay(ray, 0);
				}
				color = color / samplingAmount;
				colors.at(i).at(j) = color;
			}
		}
	};

	double const frac = std::ceil(static_cast<double>(width) / numThreads);
	tf::Taskflow taskflow;

	for (size_t i = 0; i < numThreads; ++i) {
		taskflow.silent_emplace([func, frac, i] () { func(i * frac, std::min((i + 1) * frac, static_cast<double>(width))); });
	}
	tf::Executor().run(taskflow);

	for(size_t i = 0; i < height; ++i) {
		for(size_t j = 0; j < width; ++j) {
			Color color = colors.at(i).at(j);
			ofs << (unsigned char)(255 * std::min(1.0, std::max(0.0, color.R)))
				<< (unsigned char)(255 * std::min(1.0, std::max(0.0, color.G)))
				<< (unsigned char)(255 * std::min(1.0, std::max(0.0, color.B)));
		}
	}

	ofs.close();
}
