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

using namespace std;

int main() {

	int ln = 7, index = 0;
	int msaa[] = { 0, 1, 2, 4, 8, 16, 32, 64 };

	Window::init();
	glfwWindowHint(GLFW_SAMPLES, msaa[index]);
	Window::window(1920, 1080, "Hello World", WINDOWED, true);
	Window::initGL();
	Timer::setLogFPS(true);

	//glViewport(0, 0, 1440, 900);

	glewInit();

	/* print all extensions */

	cout << glGetString(GL_VERSION) << endl;
	cout << glGetString(GL_VENDOR) << endl;

	GLubyte *image0, *image1, *image2, *image3, *imagel;

	unsigned width, height;
	image0 = IO::loadPNG(width, height, "res/textures/grass.png");
	Texture *t0 = new Texture(Texture::load2D_nicest(width, height, image0));
	cout << "loaded texture: tex0" << endl;

	unsigned width1, height1;
	image1 = IO::loadPNG(width1, height1, "res/textures/gravel.png");
	Texture *t1 = new Texture(Texture::load2D_nicest(width1, height1, image1));
	cout << "loaded texture: tex1" << endl;

	unsigned width2, height2;
	//image2 = IO::loadPNG(width2, height2, "res/textures/grass.png");
	//Texture *t2 = new Texture(Texture::load2D_nicest(width2, height2, image2));
	//cout << "loaded texture: tex2" << endl;

	unsigned width3, height3;
	//image3 = IO::loadPNG(width3, height3, "res/textures/dirt.png");
	//Texture *t3 = new Texture(Texture::load2D_nicest(width3, height3, image3));
	//cout << "loaded texture: tex3" << endl;

	unsigned widthl, heightl;
	imagel = IO::loadPNG(widthl, heightl, "res/textures/lookup3.png");
	Texture *tl = new Texture(Texture::load2D_nicest(widthl, heightl, imagel));
	cout << "loaded texture: lookup" << endl;

	Mesh *m0, *m1;

	const StaticMeshVertex verticesz[] {
		StaticMeshVertex(-2, -2, 0, 0),
		StaticMeshVertex(2, -2, 1, 0),
		StaticMeshVertex(2, 2, 1, 1),
		StaticMeshVertex(-2, 2, 0, 1),
	};
	const GLushort indicesz[] = {
		0, 1, 2, 0, 2, 3
	};

	m0 = StaticMesh::load(verticesz, sizeof(verticesz) /* (4 elements) * (4 floats in struct) * (sizeof(float) == 4)  ==  64  ==  sizeof(the_array) */, indicesz, sizeof(indicesz));

	const StaticMeshVertex verticesz1[]{
		StaticMeshVertex(-1, -1, 0, 0),
		StaticMeshVertex(2, -1, 1, 0),
		StaticMeshVertex(1, 1, 1, 1),
		StaticMeshVertex(-2, 1, 0, 1),
	};
	const GLushort indices1[] = {
		0, 1, 2, 0, 2, 3
	};

	m1 = StaticMesh::load(verticesz1, sizeof(verticesz1), indices1, sizeof(indices1));

	Transform *tr0 = new Transform(Vector2f(0, 0), 0 , Vector2f(.5, .5));

	Shader* s = Shader::load("test");

	int loc = 0;
	float ns = .4f;
	float counter_variable = 0;

	GLint res;
	glGetIntegerv(GL_SAMPLES, &res);
	cout << "samples = " << res << endl;

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	Matrix3f *proj = new Matrix3f(), *scale = new Matrix3f(), *result, *model = new Matrix3f();
	proj->initOrtho(1 * -Window::aspectRatio(), 1 * Window::aspectRatio(), -1, 1);
	//proj->initOrtho(-4, 4, -4, 4);

	Camera *cam = new Camera(Transform(), *proj);

	float x = 0, y = 0;
	const float speed = 6;

	srand(0);
	while (!Window::isCloseRequested()) {

		if (Input::eventStarted(MOUSE_WHEEL_UP))
			ns *= 1.05;
		if (Input::eventStarted(MOUSE_WHEEL_DOWN))
			ns /= 1.05;
		if (Input::event(KEY_W))
			y += speed * Timer::getDelta();
		if (Input::event(KEY_S))
			y -= speed * Timer::getDelta();
		if (Input::event(KEY_D))
			x += speed * Timer::getDelta();
		if (Input::event(KEY_A))
			x -= speed * Timer::getDelta();
		//cam->transform()->setPos(Vector2f(x, y));
		scale->initScale(ns, ns);
		Matrix3f *proj1  = *proj * scale;
		model = &(tr0->getModelMatrix());
		cam->getViewProjectionMatrix();
		result = *proj1 * model;//cam->getViewProjectionMatrix() * (model);
		glUniformMatrix3fv(loc, 1, GL_TRUE, result->getArray());

		//System::curThreadSleep(1000);

		Timer::update();
		Input::update();

		glClear(GL_COLOR_BUFFER_BIT);

		s->use();

		// enable MSAA
		glEnable(GL_MULTISAMPLE);

		//t1->bind(0);
		//m0->draw();

		t0->bind(0);
		t1->bind(1);
		//t2->bind(2);
		//t3->bind(3);
		tl->bind(4);
		glUniform1i(5, 0);
		glUniform1i(6, 1);
		//glUniform1i(7, 2);
		//glUniform1i(8, 3);
		glUniform1i(9, 4);
		m0->draw();

		// diable MSAA
		glDisable(GL_MULTISAMPLE);

		Window::update();

	}

	Window::end();
	return 0;
}