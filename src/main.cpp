#include "Scene.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"

#include <iostream>

int main () {
	Camera camera(Vector3(1, 3, 4), Vector3(0, 0, -1), Vector3(0, -1, 0), 90, 1);
	Scene scene(camera);
	//scene.addObject(new Sphere(Vector3(3.0, 0.0, 0.0), new Diffuse(Color(1.0, 0, 0), 0.8), 1.0));
	//scene.addObject(new Sphere(Vector3(5.0, 0.0, -1.2), new Dielectric(Color(1.0, 0, 0), 1.8), 1.0));
	//scene.addObject(new Sphere(Vector3(6.0, -1.0, 3.0), new Metal(Color(0.9, 0.9, 0.9), 1.0, 0.0), 2.0));
	//scene.addObject(new Sphere(Vector3(40.0, -9.0, -8.0), new Diffuse(Color(0, 1.0, 0.0), 0.8), 10.0));
	scene.addObject(new Plane(Vector3(0.0, -1.0, 0.0), new Diffuse(Color(0.7, 0.7, 0.7), 0.8), Vector3(0.0, 1.0, 0.0)));
	scene.addObject(new Sphere(Vector3(-1.0, 0.0, -2.0), new Diffuse(Color(1.0, 0.0, 0.0), 0.8), 1.0));
	scene.addObject(new Sphere(Vector3(1.0, 0.0, -2.0), new Dielectric(Color(0.0, 0.0, 1.0), 1.5), 1.0));
	scene.addObject(new Sphere(Vector3(3.0, 0.0, -2.0), new Diffuse(Color(0.0, 0.0, 1.0), 0.8), 1.0));
	scene.createImage("test.ppm", 1);

	return 0;
}
