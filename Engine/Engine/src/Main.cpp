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

using namespace std;

void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar);

// char* toS(int x) {
//	int digits[6], ln;
//	bool neg = (x < 0);
//
//	if (neg) x = -x;
//
//	for (ln = 0; 10 <= x; ln++) {
//		digits[ln] = x % 10;
//		x /= 10;
//	}
//	digits[ln++] = x % 10;
//
//	//cout << ln << endl;
//
//	if (neg) ln++;
//
//	char* res = new char[ln + 1];
//
//	int i = 0;
//
//	if (neg)
//		res[i] = '-';
//
//	for (; i < ln; i++) {
//		res[(neg) ? i + 1 : i] = 48 + digits[i];
//		//cout << digits[i] << endl;
//	}
//
//	res[ln] = '\n';
//
//	return res;
//}


//GLuint LoadShader() {
//	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
//	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
//
//	// Read shaders
//	std::string vertShaderStr = "#version 120\nattribute vec2 position;\nuniform mat3 MVP;\nvoid main() {\ngl_Position = vec4(MVP * vec3(position, 1.0), 1);\n}";
//	std::string fragShaderStr = "#version 120\nvoid main() {\ngl_FragColor = vec4(1, 0, 0.5, 1);\n}";
//	const char *vertShaderSrc = vertShaderStr.c_str();
//	const char *fragShaderSrc = fragShaderStr.c_str();
//
//	GLint result = GL_FALSE;
//	int logLength;
//
//	// Compile vertex shader
//	std::cout << "Compiling vertex shader." << std::endl;
//	glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
//	glCompileShader(vertShader);
//
//	// Compile fragment shader
//	std::cout << "Compiling fragment shader." << std::endl;
//	glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
//	glCompileShader(fragShader);
//
//	std::cout << "Linking program" << std::endl;
//	GLuint program = glCreateProgram();
//	glAttachShader(program, vertShader);
//	glAttachShader(program, fragShader);
//	glLinkProgram(program);
//
//	glGetProgramiv(program, GL_LINK_STATUS, &result);
//	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
//	std::vector<char> programError((logLength > 1) ? logLength : 1);
//	glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
//	std::cout << &programError[0] << std::endl;
//
//	glDeleteShader(vertShader);
//	glDeleteShader(fragShader);
//
//	return program;
//}

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
	cout << pos->toString() << endl;


	Timer::setLogFPS(false);

	int length = 0;
	DisplayMode* dmodes = Window::getAvailableDisplayModes(&length, ASPECT_16_9);


	//int program = LoadShader();



	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, Window::getWidth(), Window::getHeight());
	glMatrixMode(GL_MODELVIEW);
	glPointSize(10);

	Input::mouseGrab(true);

	float ry = 0, rx = 0, zm = -4, time = 0;
	int i = 0;




	//GLuint vbo, ibo;
	//glGenBuffers(1, &vbo);
	//glGenBuffers(1, &ibo);
	//int size = 6;

	//float  vertices[] = { 0, 0, 2, 4, 4, 0 };
	//int indices[] = {0,1,2};

	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, 6, vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3, indices, GL_STATIC_DRAW);
	float rot = 0;
	while (!Window::isCloseRequested()) {
		glClear(GL_COLOR_BUFFER_BIT);
		
		Timer::update();

		rot += Timer::getDelta();
		Input::update();
		Vector2f* p = ortho*(transform* pos);

		glRectf(p->getX() - 1, p->getY() -1, p->getX() + 1, p->getY() + 1);

		/*glUseProgram(program);
		glUniformMatrix3fv(0, 0, 9, ortho.getArray());
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);*/
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
