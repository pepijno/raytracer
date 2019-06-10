#pragma once

#include <cmath>

struct Color {
	double R = 0.0;
	double G = 0.0;
	double B = 0.0;
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

struct Material {
	Color color;
	bool isCheckered;

	Material(Color const c, bool const i): color(c), isCheckered(i) {};

	Color getColor(Vector3 const hitPoint) const {
		if (this->isCheckered) {
			int const s = std::floor(hitPoint.getX());
			int const t = std::floor(hitPoint.getZ());
			if (((s + t) % 2) == 0) {
				return BLACK;
			}
		}
		return this->color;
	};
};
