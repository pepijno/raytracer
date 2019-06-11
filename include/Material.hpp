#pragma once

#include "Intersection.hpp"
#include <cmath>

struct Color {
	double R = 0.0;
	double G = 0.0;
	double B = 0.0;
	Color() {};
	Color(double const i) : R(i), G(i), B(i) {};
	Color(double const Ri, double const Gi, double const Bi) : R(Ri), G(Gi), B(Bi) {};

	Color operator*(Color const c) { return Color(this->R * c.R, this->G * c.G, this->B * c.B); };

	Color operator*(double const d) { return Color(this->R * d, this->G * d, this->B * d); };
	Color operator/(double const d) { return Color(this->R / d, this->G / d, this->B / d); };
	Color operator+(Color const d) { return Color(this->R + d.R, this->G + d.G, this->B + d.B); };
	bool operator==(Color const d) { return this->R == d.R && this->G == d.G && this->B == d.B; };
};

inline std::ostream& operator<<(std::ostream& str, Color const c) {
	return str << "{" << c.R << "," << c.G << "," << c.B << "} ";
}

Color const BLACK = Color(0.0);
Color const WHITE = Color(1.0);

class Scene;

struct Material {
	Color color;

	Material(Color const c): color(c) {};
	virtual ~Material() {};

	virtual Color const getColor(Intersection const intersection, Scene const* scene, int8_t const depth) = 0;
};

struct Diffuse : public Material {
	double albedo;

	Diffuse(Color const c, double const a) : Material(c), albedo(a) {};

	virtual Color const getColor(Intersection const intersection, Scene const* scene, int8_t const depth);
};

struct Metal : public Diffuse {
	double fuzz;

	Metal(Color const c, double const a, double const f) : Diffuse(c, a), fuzz(f) {};

	Color const getColor(Intersection const intersection, Scene const* scene, int8_t const depth);
};

struct Dielectric : public Material {
	double refractionIndex;

	Dielectric(Color const c, double const r) : Material(c), refractionIndex(r) {};

	Color const getColor(Intersection const intersection, Scene const* scene, int8_t const depth);
};
