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

#define BUFFER_OFFSET(offset) ((void *)(offset))
#define GLSL(version, src) version "\n" #src

using namespace std;

int main() {

	int ln = 7, index = 7;
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

	GLubyte *image0, *image1;

	unsigned width, height;
	image0 = IO::loadPNG(width, height, "res/textures/test.png");
	Texture *t = new Texture(Texture::load2D_nicest(width, height, image0));

	unsigned width1, height1;
	image1 = IO::loadPNG(width1, height1, "res/textures/bricks.png");
	Texture *t1 = new Texture(Texture::load2D_nicest(width1, height1, image1));

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

	Transform *tr0 = new Transform(Vector2f(2, 2), 30, Vector2f(0.1, 0.1));

	Shader* s = Shader::load("test");

	int loc = 0;
	float ns = 2;

	GLint res;
	glGetIntegerv(GL_SAMPLES, &res);
	cout << "samples = " << res << endl;

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	Matrix3f *proj = new Matrix3f(), *scale = new Matrix3f(), *result, *model = new Matrix3f();
	proj->initOrtho(1 * -Window::aspectRatio(), 1 * Window::aspectRatio(), -1, 1);

	srand(0);
	while (!Window::isCloseRequested()) {

		ns = sinf(System::timeSec()) * 2 + 3;
		scale->initScale(1 / ns, 1 / ns);
		model = &(tr0->getmodelMatrix());
		result = (*proj) * (model);
		glUniformMatrix3fv(loc, 1, GL_TRUE, result->getArray());

		Timer::update();
		Input::update();

		glClear(GL_COLOR_BUFFER_BIT);

		s->use();

		// enable MSAA
		glEnable(GL_MULTISAMPLE);

		t1->bind(0);
		m0->draw();

		t->bind(0);
		m1->draw();

		// diable MSAA
		glDisable(GL_MULTISAMPLE);

		Window::update();

	}

	Window::end();
	return 0;
}