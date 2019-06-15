#include "Scene.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"

#include <iostream>

int main () {
	Vector3 const lookFrom(3, 3, 2);
	Vector3 const lookAt(1.0, 0.0, -2.0);
	double const focusDistance = std::sqrt((lookFrom - lookAt).lengthSquared());
	Camera camera(lookFrom, lookAt, Vector3(0, -1, 0), 90, 1, 1.0, focusDistance);
	Scene scene(camera);
	scene.addObject(new Plane(Vector3(0.0, -1.0, 0.0), new Diffuse(Color(0.7, 0.7, 0.7), 0.8), Vector3(0.0, 1.0, 0.0)));
	scene.addObject(new Sphere(Vector3(-1.0, 0.0, -2.0), new Diffuse(Color(1.0, 0.0, 0.0), 0.8), 1.0));
	scene.addObject(new Sphere(Vector3(1.0, 0.0, -2.0), new Dielectric(Color(0.0, 0.0, 1.0), 1.8), 1.0));
	scene.addObject(new Sphere(Vector3(3.0, 0.0, -2.0), new Diffuse(Color(0.0, 0.0, 1.0), 0.8), 1.0));
	scene.createImage("test.ppm", 8);

	return 0;
}
