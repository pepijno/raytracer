#pragma once

#include <memory>
#include <vector>

#include "Object.hpp"
#include "Camera.hpp"
#include "Ray.hpp"
#include "Vector3.hpp"

class Scene {
private:
	Camera camera;
	std::vector<std::unique_ptr<Object>> objects;

public:
	Scene(Camera const c): camera(c) {};

	void addObject(Object* object);

	void createImage(std::string const fileName, size_t const numThreads) const;

	Color traceRay(Ray const& ray, int8_t const depth) const;
};
