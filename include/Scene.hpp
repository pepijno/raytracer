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
	std::vector<Vector3> lights;

	Color traceRay(Ray const& ray) const;
public:
	Scene(Camera camera): camera(camera) {};

	void addObject(Object* object);
	void addLight(Vector3 source);

	void createImage(std::string const fileName) const;
};
