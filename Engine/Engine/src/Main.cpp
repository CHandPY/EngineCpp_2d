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

	// textures tests

	GLubyte *image0, *image1;

	unsigned width, height;
	image0 = IO::loadPNG(width, height, "test.png");
	Texture *t = new Texture(Texture::load2D_nicest(width, height, image0));

	unsigned width1, height1;
	image1 = IO::loadPNG(width1, height1, "bricks.png");
	Texture *t1 = new Texture(Texture::load2D_nicest(width1, height1, image1));
	//t->bind(0);


	// VBO + IBO
	GLuint vbo, vbo1;
	GLuint ibo, ibo1;

	const GLfloat vertices[] = {
		-2.0f, -2.0f, 0.0f, 1.0f,
		2.0f, -2.0f, 0.0f, 1.0f,
		-2.0f, 2.0f, 0.0f, 1.0f,
		2.0f, 2.0f, 0.0f, 1.0f,
	};
	const GLfloat vertex_colors[] = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f
	};
	const GLfloat vertex_tex[] = {
		0, 0,
		1, 0,
		0, 1,
		1, 1
	};
	static const GLushort vertex_indices[] = {
		0, 1, 2, 1, 3, 2
	};

	const GLfloat vertices1[] = {
		-1.0f, -1.0f, 0.0f, 1.0f,
		2.0f, -1.0f, 0.0f, 1.0f,
		-2.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
	};
	const GLfloat vertex_colors1[] = {
		0.0f, 0.0f, 0.3f, 1.0f,
		0.0f, 0.0f, 0.3f, 1.0f,
		0.0f, 0.0f, 0.3f, 1.0f,
		0.0f, 0.0f, 0.3f, 1.0f
	};
	const GLfloat vertex_tex1[] = {
		0, 0,
		1, 0,
		0, 1,
		1, 1
	};
	const GLushort vertex_indices1[] = {
		0, 1, 2, 1, 3, 2
	};

	Mesh *m0 = new Mesh(Mesh::load(vertices, sizeof(vertices), vertex_tex, sizeof(vertex_tex), vertex_indices, sizeof(vertex_indices))),
		 *m1 = new Mesh(Mesh::load(vertices1, sizeof(vertices1), vertex_tex1, sizeof(vertex_tex1), vertex_indices1, sizeof(vertex_indices1)));

	Shader* s = Shader::load("test");//Shader::load(getVS().c_str(), getFS().c_str());
	s->use();

	int loc = 0;
	float ns = 2;

	GLint res;
	glGetIntegerv(GL_SAMPLES, &res);
	cout << "samples = " << res << endl;

	Matrix3f *proj = new Matrix3f(), *scale = new Matrix3f(), *result;
	proj->initOrtho(1 * -Window::aspectRatio(), 1 * Window::aspectRatio(), -1, 1);

	srand(0);
	while (!Window::isCloseRequested()) {

		ns = sinf(System::timeSec()) * 2 + 3;
		scale->initScale(1 / ns, 1 / ns);
		result = (*proj) * (scale);
		glUniformMatrix3fv(loc, 1, GL_TRUE, result->getArray());

		glClear(GL_COLOR_BUFFER_BIT);

		Timer::update();
		Input::update();

		if (Input::eventStarted(KEY_SPACE)) {
			//glfwWindowHint(GLFW_SAMPLES, msaa[++index % ln]);
			cout << msaa[++index % ln] << endl;
			//Window::window(1920, 1080, "Hello World", WINDOWED, true);
			//Window::initGL();
		}

		s->use();
		// enable MSAA
		glEnable(GL_MULTISAMPLE);

		// render meshes

		//glUseProgram(program);

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