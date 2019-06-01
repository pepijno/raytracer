#pragma once

#include "Vector3.hpp"

class Object {
protected:
	Vector3 origin;
public:
	Object(Vector3 const origin): origin(origin) {};
};
