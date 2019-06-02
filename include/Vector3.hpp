#pragma once

#include <ostream>

class Vector3 {
private:
	double x;
	double y;
	double z;
public:
	Vector3(double x, double y, double z): x(x), y(y), z(z) {};

	double innerProduct(Vector3 const other) const;
	Vector3 outerProduct(Vector3 const other) const;
	double lengthSquared() const;
	Vector3 normalized() const;

	Vector3 operator+(Vector3 const other) const;
	Vector3 operator-(Vector3 const other) const;
	Vector3 operator*(double scalar) const;

	double getX() const { return this->x; };
	double getY() const { return this->y; };
	double getZ() const { return this->z; };
};

inline std::ostream& operator<<(std::ostream& str, Vector3 const& v) {
	return str << "(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ") ";
}