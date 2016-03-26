#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include <stdio.h>

#include "core/System.h"
#include "core/Input.h"
#include "core/Window.h"
#include "core/Timer.h"
#include "core/HashMap.h"
#include "core/Strings.h"
#include "core/Shader.h"
#include "core/IO.h"
#include "core/Texture.h"
#include "core/Matrix3f.h"
#include "core/Mesh.h"
#include "core/StaticMesh.h"
#include "core/Transform.h"
#include "core/Camera.h"

#define BUFFER_OFFSET(offset) ((void *)(offset))

//using namespace std;
//using namespace engine;
//using namespace engine::core;
//using namespace engine::graphics;

//#include <Windows.h>
#include "core/Logger.h"

int main() {

	using namespace std;
	using namespace engine;
	using namespace engine::core;
	using namespace engine::graphics;

	int ln = 7, index = 0;
	int msaa[] = { 0, 1, 2, 4, 8, 16, 32, 64 };

	Window::init();
	glfwWindowHint(GLFW_SAMPLES, msaa[index]);
	Window::window(1920, 1080, "Hello World", WINDOWED, true);
	Window::initGL();
	Timer::setLogFPS(true);

	glewInit();

	Shader* s = Shader::load("test");

	Mesh *m0;
	const StaticMeshVertex verticesz[]{
		StaticMeshVertex(-.5, -.5, 0, 0),
		StaticMeshVertex(.5, -.5, 1, 0),
		StaticMeshVertex(.5, .5, 1, 1),
		StaticMeshVertex(-.5, .5, 0, 1),
	};
	const GLushort indicesz[] = {
		0, 1, 2, 0, 2, 3
	};
	m0 = StaticMesh::load(verticesz, sizeof(verticesz) /* (4 elements) * (4 floats in struct) * (sizeof(float) == 4)  ==  64  ==  sizeof(the_array) */, indicesz, sizeof(indicesz));

	/// MATRIX TEST ///

	Matrix3f *proj = new Matrix3f(), *res = new Matrix3f(), *trm = new Matrix3f();
	proj->initOrtho(2 * -Window::aspectRatio(), 2 * Window::aspectRatio(), -2, 2);
	trm->initTranslation(1, 1);

	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);

	unsigned width, height;
	GLubyte *image0 = IO::loadPNG(width, height, "res/textures/bricks.png");
	Texture *t0 = new Texture(Texture::load2D_nicest(width, height, image0));
	//cout << "loaded texture: tex0" << endl;
	PASS("loaded texture: tex0");
	WRN("test warning");
	ERR("test error");

	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);

	Matrix3f mat1 = Matrix3f();
	mat1.initTranslation(0, 0);

	Transform *tr = new Transform();
	tr->setPos(new Vector2f(0, 0));

	Camera *cam = new Camera(new Transform(new Vector2f(1, 0)), Ortho::square_num(4, Window::aspectRatio()));

	float x = 0, y = 0, speed = 3;

	float cnt = 0;

	Vector2f* vec2 = new Vector2f(3, 3);
	Transform *tr0 = new Transform(vec2);
	Matrix3f *mat00 = new Matrix3f();
	Matrix3f *mat01 = new Matrix3f();
	Matrix3f *mat02 = new Matrix3f();

	Matrix3f *mvp = nullptr;

	while (!Window::isCloseRequested() && !Input::eventStarted(KEY_ESCAPE)) {

		Timer::update();
		Input::update();

		
		if (Input::event(KEY_W))
			y += speed * Timer::getDelta();
		if (Input::event(KEY_S))
			y -= speed * Timer::getDelta();
		if (Input::event(KEY_D))
			x += speed * Timer::getDelta();
		if (Input::event(KEY_A))
			x -= speed * Timer::getDelta();

		cam->transform()->getPos()->set(x, y);

		s->use();
		delete mvp;
		mvp = cam->getViewProjectionMatrix()->operator*(tr->getModelMatrix());
		glUniformMatrix3fv(0, 1, GL_TRUE, mvp->getArray()); 

		glClear(GL_COLOR_BUFFER_BIT);

		t0->bind(0);
		glUniform1i(5, 0);
		m0->draw();

		Window::update();
	}

	Window::end();
	return 0;
	
}
