#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>

#include "core/System.h"
#include "core/Input.h"
#include "core/Window.h"
#include "core/Timer.h"
#include "core/HashMap.h"
#include "core/Strings.h"
#include "core/Matrix3f.h"
#include "Apple.h"

#include "core/Strings.h"

using namespace std;

void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar);

string getVS() {
	return "#version 120\n" + nextline
		+  "attribute vec2 position;" + nextline
		+  "uniform mat3 MVP;" + nextline 
		+  "void main() {" + nextline 
		+  "gl_Position = gl_ModelViewProjectionMatrix * vec4(position, 0, 1);" + nextline 
		+  "}"; // vec4(ftransform().xyz, 1);
}

string getFS() {
	return "#version 120" + nextline
		+  "void main() {" + nextline
		+  "gl_FragColor = vec4(1, 1, 1, 1);" + nextline
		+  "}";
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

	Apple a = Apple("Bob", 0xffffaa00, 7.2, 0.0221);
	cout << a.toString() << endl;

	Window::init();
	Window::window(1920, 1080, "Hello World", WINDOWED, false);
	Window::initGL();

	Vector2f *pos = new Vector2f(0, 0);

	Matrix3f scale = Matrix3f();
	scale.initScale(1, 1);
	Matrix3f rotation = Matrix3f();
	rotation.initRotation(0);
	cout << rotation.toString() << endl;
	Matrix3f translation = Matrix3f();
	translation.initTranslation(0, 0);
	Matrix3f transform = Matrix3f();
	transform.initTransform(&scale, &rotation, &translation);
	cout << transform.toString() << endl;
	Matrix3f ortho = Matrix3f();
	ortho.initOrtho(-5 * Window::aspectRatio(),5 * Window::aspectRatio(), -5 , 5 );
	cout << ortho.toString() << endl;
	cout << pos->toString() << endl;

	pos = transform* pos;
	std::cout << pos->toString() << endl;


	Timer::setLogFPS(false);

	int length = 0;
	DisplayMode* dmodes = Window::getAvailableDisplayModes(&length, ASPECT_16_9);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, Window::getWidth(), Window::getHeight());
	glMatrixMode(GL_MODELVIEW);
	//glPointSize(10);

	Input::mouseGrab(false);

	float ry = 0, rx = 0, zm = -4, time = 0;
	int i = 0;


	glewInit();

	int program = LoadShader();

	GLuint vbo, ibo;
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	int size = 6;

	float  vertices[] = { -1, -1, 0, 1, 1, -1 };
	int indices[] = {0,1,2};

	int numvert = 3;
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * numvert, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 2 * numvert, vertices);

	int numind = 3;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * numind, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(GLuint)*numind, indices);

	float rot = 0;

	while (!Window::isCloseRequested()) {
		glClear(GL_COLOR_BUFFER_BIT);
		
		Timer::update();

		//rot += Timer::getDelta();
		Input::update();
		/*Vector2f* p = ortho*(transform* pos);

		glBegin(GL_POINTS);
		glVertex2f(p->getX(), p->getY());
		glEnd();*/

		//glRectf(p->getX() - 1, p->getY() -1, p->getX() + 1, p->getY() + 1);

		rot += Timer::getDelta();

		
		//glUseProgram(program);
		//glUniform1f(0, rot);
		//glUniformMatrix3fv(0, 9, GL_FALSE, new float[9] { 1, 0, 1, 1, 0, 0, 1, 0, 0});
		//glUniformMatrix3fv(0, 1, GL_FALSE, ortho.getArray());

		//glRectf(0, 0, 3, 3);

		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		//glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(GLfloat) * 2, NULL);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);
		glDisableClientState(GL_VERTEX_ARRAY);

		//glDrawElements(GL_TRIANGLES, 1, GL_UNSIGNED_INT, indices);

		glDisableVertexAttribArray(0);
		

		Window::update();

	}

	Window::end();

	return 0;

}




/* TEMP perspective Matrix */
void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar) {
	const GLdouble pi = 3.1415926535897932384626433832795;
	GLdouble fW, fH;
	fH = tan(fovY / 360 * pi) * zNear;
	fW = fH * aspect;
	glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}
