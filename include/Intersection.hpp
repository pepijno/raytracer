#pragma once

#include "Vector3.hpp"
#include "Ray.hpp"

struct Intersection {
	bool isIntersect;
	double t;
	Vector3 hitPoint;
	Vector3 hitNormal;
	Ray ray;

	Intersection(bool const isI): isIntersect(isI), t(0.0), hitPoint(Vector3()), hitNormal(Vector3()), ray(Ray()) {};
	Intersection(bool const isI, double const ti, Vector3 const hP, Vector3 const hN, Ray const r): isIntersect(isI), t(ti), hitPoint(hP), hitNormal(hN), ray(r) {};
};
