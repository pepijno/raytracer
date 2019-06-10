#pragma once

#include "Vector3.hpp"
#include "Material.hpp"
#include "Ray.hpp"
#include "Intersection.hpp"

#include <memory>

class Scene;

class Object {
protected:
	Vector3 origin;
	Material* material;
public:
	Object(Vector3 const o, Material* m): origin(o) {
		this->material = std::move(m);
	};
	virtual ~Object() {};
	virtual Intersection intersect(Ray const& ray) const = 0;
	Color getColor(Intersection const intersection, Scene const* scene, int8_t const depth) const { return this->material->getColor(intersection, scene, depth); };
	Vector3 getOrigin() const { return this->origin; };
};
