#pragma once

#include <memory>
#include <vector>

#include "Object.hpp"
#include "Camera.hpp"
#include "Ray.hpp"

struct Color {
	uint32_t R;
	uint32_t G;
	uint32_t B;
	Color(uint32_t R, uint32_t G, uint32_t B) : R(R), G(G), B(B) {};
};

class Scene {
private:
	Camera camera;
	std::vector<std::unique_ptr<Object>> objects;

	Color traceRay(Ray const& ray) const;
public:
	Scene(Camera camera): camera(camera) {};

	void addObject(Object* object);

	void createImage(std::string const fileName) const;
};
