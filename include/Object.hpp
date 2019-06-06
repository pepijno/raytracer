#pragma once

#include "Vector3.hpp"
#include "Material.hpp"
#include "Ray.hpp"

struct Intersection {
	bool isIntersect;
	double t;
	Vector3 hitPoint;
	Vector3 hitNormal;

	Intersection(bool const isI): isIntersect(isI), t(0.0), hitPoint(Vector3()), hitNormal(Vector3()) {};
	Intersection(bool const isI, double const ti, Vector3 const hP, Vector3 const hN): isIntersect(isI), t(ti), hitPoint(hP), hitNormal(hN) {};
};

class Object {
protected:
	Vector3 origin;
	Material material;
public:
	Object(Vector3 const o, Material const m): origin(o), material(m) {};
	virtual ~Object() {};
	virtual Intersection intersect(Ray const& ray) const = 0;
	Color getColor(Vector3 const hitPoint) const { return this->material.getColor(hitPoint); };
	Vector3 getOrigin() const { return this->origin; };
};
