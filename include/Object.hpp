#pragma once

#include "Vector3.hpp"
#include "Ray.hpp"

struct Intersection {
	bool isIntersect;
	double t;

	Intersection(bool isIntersect, double t): isIntersect(isIntersect), t(t) {};
};

struct Color {
	uint32_t R;
	uint32_t G;
	uint32_t B;
	Color(uint32_t R, uint32_t G, uint32_t B) : R(R), G(G), B(B) {};

	Color operator*(double const d) { return Color(this->R * d, this->G * d, this->B * d); };
	Color operator+(Color const d) { return Color(this->R + d.R, this->G + d.G, this->B + d.B); };
};

inline std::ostream& operator<<(std::ostream& str, Color const c) {
	return str << "{" << c.R << "," << c.G << "," << c.B << "} ";
}

Color const BLACK = Color(0, 0, 0);

class Object {
protected:
	Vector3 origin;
	Color color;
public:
	Object(Vector3 const origin, Color const color): origin(origin), color(color) {};
	virtual Intersection intersect(Ray const& ray) const = 0;
	Color getColor() const { return this->color; };
	Vector3 getOrigin() const { return this->origin; };
};
