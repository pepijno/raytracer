#include "Scene.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"

int main () {
	Camera camera(Vector3(0.0, -1.0, 0.0), Vector3(-1.0, 0.0, 1.0), Vector3(1.0, 0.0, 1.0), Vector3(-1.0, 0.0, -1.0));
	Scene scene(camera);
	scene.addObject(new Sphere(Vector3(0.0, 3.0, 0.0), 1.0));
	scene.createImage("test.bmp");

	return 0;
}
