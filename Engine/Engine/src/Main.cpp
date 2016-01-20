
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

#include "core/lodepng.h"

#define BUFFER_OFFSET(offset) ((void *)(offset))
#define GLSL(version, src) version "\n" #src

using namespace std;

float * initOrtho(float left, float right, float bottom, float top) {
	float * m_mat = new float[9];
	m_mat[0] = 2 / (right - left);
	m_mat[1] = 0;
	m_mat[2] = -(right + left) / (right - left);
	m_mat[3] = 0;
	m_mat[4] = 2 / (top - bottom);
	m_mat[5] = -(top + bottom) / (top - bottom);
	m_mat[6] = 0;
	m_mat[7] = 0;
	m_mat[8] = 1;
	return m_mat;
}

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
	/*
	const GLubyte* s = glGetString(GL_EXTENSIONS);
	int i = 0;
	while (s[i] != 0) {
	if (s[i] == ' ')
	cout << "\n";
	else
	cout << s[i];
	i++;
	}
	*/

	// textures tests

	std::vector<unsigned char> image;
	unsigned width, height;
	//unsigned error = lodepng::decode(image, width, height, "test.png");
	//cout << error << endl;

	GLubyte *imageFix;// = new GLubyte[image.size()];
	//int mod = sizeof(unsigned char);
	//int side = int(sqrtf(image.size() / 4));

	//int cnt = 0;
	//for (int x = side - 1; x >= 0; x--) {
		//for (int y = 0; y < side; y++) {
			//imageFix[(y + (x * side)) * 4 + 0] = image[cnt++];
			//imageFix[(y + (x * side)) * 4 + 1] = image[cnt++];
			//imageFix[(y + (x * side)) * 4 + 2] = image[cnt++];
			//imageFix[(y + (x * side)) * 4 + 3] = image[cnt++];
		//}
	//}

	imageFix = IO::loadPNG(width, height, "test.png");

	srand(0);

	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
	glTexSubImage2D(GL_TEXTURE_2D, // target
		0, // First mipmap level
		0, 0, // x and y offset
		width, height, // width and height
		GL_RGBA, GL_UNSIGNED_BYTE, // format and type
		imageFix);//&image[0]);
	
	// VBO + IBO
	GLuint vbo, vbo1;
	GLuint ibo, ibo1;

	const GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f, 1.0f,
		0.8f, -1.0f, 0.0f, 1.0f,
		-0.8f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
	};
	const GLfloat vertex_colors[] = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f
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
	static const GLushort vertex_indices1[] = {
		0, 1, 2, 1, 3, 2
	};

	// gen Mesh 0
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(vertex_colors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(vertex_colors), vertex_colors);

	// gen Mesh 1
	glGenBuffers(1, &ibo1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices1), vertex_indices, GL_STATIC_DRAW);

	glGenBuffers(1, &vbo1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1) + /*sizeof(vertex_colors1)*/ sizeof(vertex_tex1) , NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices1), vertices1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices1), sizeof(vertex_tex1), vertex_tex1);
	//glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices1), sizeof(vertex_colors1), vertex_colors1);

	Shader* s = Shader::load("test");//Shader::load(getVS().c_str(), getFS().c_str());
	s->use();

	int loc = 0;
	//loc = glGetUniformLocation(program, "proj");
	//glUniformMatrix3fv(loc, 1, GL_TRUE, initOrtho(- 2,  2, -2, 2));
	float ns;

	float i = 0, j = 0, k = 0;

	GLint res;
	glGetIntegerv(GL_SAMPLES, &res);
	cout << "samples = " << res << endl;

	srand(0);
	while (!Window::isCloseRequested()) {

		ns = sinf(System::timeSec()) * 2 + 3;
		glUniformMatrix3fv(loc, 1, GL_TRUE, initOrtho(ns * -Window::aspectRatio(), ns * Window::aspectRatio(), -ns, ns));

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

		// enable the arrays
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		// bind VBO and pass vertex attribs for mesh1
		glBindBuffer(GL_ARRAY_BUFFER, vbo1);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices)));
		//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices)));
		// render mesh1
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo1);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));

		//glUseProgram(program);

		// bind VBO and pass vertex attribs for mesh0
		//glBindBuffer(GL_ARRAY_BUFFER, vbo);
		//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices1)));
		// render mesh0
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// diable MSAA
		glDisable(GL_MULTISAMPLE);

		Window::update();

	}

	Window::end();
	return 0;
}

double hm(int n) {
	if (n <= 1) return 1;
	return (1 / n) + hm(n - 1);
}