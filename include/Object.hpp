#pragma once

#include "Vector3.hpp"
#include "Ray.hpp"

struct Intersection {
	bool isIntersect;
	double t;

	Intersection(bool const isI, double const ti): isIntersect(isI), t(ti) {};
};

struct Color {
	double R;
	double G;
	double B;
	Color(double const Ri, double const Gi, double const Bi) : R(Ri), G(Gi), B(Bi) {};

	Color operator*(double const d) { return Color(this->R * d, this->G * d, this->B * d); };
	Color operator/(double const d) { return Color(this->R / d, this->G / d, this->B / d); };
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
	Object(Vector3 const o, Color const c): origin(o), color(c) {};
	virtual ~Object() {};
	virtual Intersection intersect(Ray const& ray) const = 0;
	Color getColor() const { return this->color; };
	Vector3 getOrigin() const { return this->origin; };
};
