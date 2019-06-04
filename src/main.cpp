#include "Scene.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"

int main () {
	Camera camera(Vector3(0.0, -3.0, 0.0), Vector3(-1.0, 0.0, 1.0), Vector3(1.0, 0.0, 1.0), Vector3(-1.0, 0.0, -1.0));
	Scene scene(camera);
	scene.addObject(new Sphere(Vector3(0.0, 3.0, 0.0), Color(255, 0, 0), 1.0));
	scene.addObject(new Sphere(Vector3(1.0, 6.0, 0.0), Color(0, 0, 255), 2.0));
	scene.addLight(Vector3(3.0, -2.0, 3.0));
	scene.createImage("test.ppm");

	return 0;
}
