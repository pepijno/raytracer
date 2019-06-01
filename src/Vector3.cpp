#include "Vector3.hpp"

#include <cmath>

double Vector3::innerProduct(Vector3 const other) const {
	return this->x * other.x + this->y * other.y + this->z * other.z;
}

Vector3 Vector3::outerProduct(Vector3 const other) const {
	return Vector3(
			this->y * other.z - this->z * other.y,
			this->z * other.x - this->x * other.z,
			this->x * other.y - this->y * other.x
			);
}

double Vector3::lengthSquared() const {
	return this->innerProduct(*this);
}

Vector3 Vector3::normalized() const {
	return (*this) * (1.0 / sqrt(this->lengthSquared()));
}

Vector3 Vector3::operator+(Vector3 const other) const {
	return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vector3 Vector3::operator-(Vector3 const other) const {
	return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
}

Vector3 Vector3::operator*(double scalar) const {
	return Vector3(this->x * scalar, this->y * scalar, this->z * scalar);
}
