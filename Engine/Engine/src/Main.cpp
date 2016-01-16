
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

#include "Apple.h"





#define BUFFER_OFFSET(offset) ((void *)(offset))
#define GLSL(version, src) version "\n" #src

using namespace std;

string nextline = "\n";

string getVS() {
	return GLSL("#version 430 core",
	layout(location = 0) in vec2 vPosition;
	layout(location = 1) in vec3 color;
	uniform mat3 proj; 
	out vec3 col;
	void main() {
		col = color;
		gl_Position = vec4(proj * vec3(vPosition, 0), 1);
	}
	); // vec4(ftransform().xyz, 1);
}

string getFS() {
	return GLSL("#version 430 core", 
	out vec4 fragColor;
	sample in vec3 col;
	void main() {
		fragColor = vec4(col, 1.0);
	}
	);
}

float * initOrtho(float left, float right, float bottom, float top) {
	float * m_mat = new float[9];
	m_mat[0] = 3 / (right - left);
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

GLuint LoadShader() {
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Read shaders
	std::string vertShaderStr = getVS();
	std::string fragShaderStr = getFS();
	const char *vertShaderSrc = vertShaderStr.c_str();
	const char *fragShaderSrc = fragShaderStr.c_str();

	GLint result = GL_FALSE;
	int logLength;

	// Compile vertex shader
	std::cout << "Compiling vertex shader." << std::endl;
	glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
	glCompileShader(vertShader);

	// Compile fragment shader
	std::cout << "Compiling fragment shader." << std::endl;
	glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
	glCompileShader(fragShader);

	int comp1;
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &comp1);

	std::cout << "Linking program" << std::endl;
	GLuint program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<char> programError((logLength > 1) ? logLength : 1);
	glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
	std::cout << &programError[0] << std::endl;

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	return program;
}

int main() {
	char test[1024];
	FILE *fp = fopen("C:\\Users\\Pierre-Yves\\Desktop\\test.txt", "r");
	fgets(test, 1023, fp); 
	printf("%s", test);







	int ln = 7, index = 5;
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
		-2.0f, -2.0f, 0.0f, 1.0f,
		2.0f, -2.0f, 0.0f, 1.0f,
		-2.0f, 2.0f, 0.0f, 1.0f,
		2.0f, 2.0f, 0.0f, 1.0f,
	};
	const GLfloat vertex_colors1[] = {
		0.0f, 0.0f, 0.3f, 1.0f,
		0.0f, 0.0f, 0.3f, 1.0f,
		0.0f, 0.0f, 0.3f, 1.0f,
		0.0f, 0.0f, 0.3f, 1.0f
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1) + sizeof(vertex_colors1), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices1), vertices1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices1), sizeof(vertex_colors1), vertex_colors1);

	// FOR VAO
	//GLuint vao, buffer;
	//
	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);
	//
	//GLfloat vertices[6][2] = {
	//	{ -0.50, -0.50 }, // Triangle 1
	//	{ 0.50, -0.50 },
	//	{ -0.50, 0.50 },
	//	{ 0.50, -0.50 }, // Triangle 2
	//	{ 0.50, 0.50 },
	//	{ -0.50, 0.50 }
	//};
	//
	//glGenBuffers(1, &buffer);
	//glBindBuffer(GL_ARRAY_BUFFER, buffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	//glEnableVertexAttribArray(0);

	//GLuint program = LoadShader();
	//glUseProgram(program);

	Shader* s = Shader::load(getVS().c_str(), getFS().c_str());
	s->use();

	int loc = 0;
	//loc = glGetUniformLocation(program, "proj");
	glUniformMatrix3fv(loc, 1, GL_TRUE, initOrtho(-Window::aspectRatio() * 1, Window::aspectRatio() * 1, -1, 1));
	//glUniformMatrix3fv(loc, 1, GL_TRUE, initOrtho(-1, 1, -1, 1));

	float i = 0, j = 0, k = 0;

	GLint res;
	glGetIntegerv(GL_SAMPLES, &res);
	cout << "samples = " << res << endl;


	while (!Window::isCloseRequested()) {
		glClear(GL_COLOR_BUFFER_BIT);

		Timer::update();
		Input::update();

		if (Input::eventStarted(KEY_SPACE)) {
			//glfwWindowHint(GLFW_SAMPLES, msaa[++index % ln]);
			cout << msaa[++index % ln] << endl;
			//Window::window(1920, 1080, "Hello World", WINDOWED, true);
			//Window::initGL();
		}

		// enable MSAA
		glEnable(GL_MULTISAMPLE);

		struct quat {
			float x, y, z, w;
		};

		// render meshes

		//glUseProgram(program);

		// enable the arrays
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		// bind VBO and pass vertex attribs for mesh1
		glBindBuffer(GL_ARRAY_BUFFER, vbo1);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices)));
		// render mesh1
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo1);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));

		//glUseProgram(program);

		// bind VBO and pass vertex attribs for mesh0
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices1)));
		// render mesh0
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// diable MSAA
		glDisable(GL_MULTISAMPLE);

		Window::update();

	}

	Window::end();
	return 0;
}
