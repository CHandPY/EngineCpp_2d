#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>

using namespace std;

#include "core/System.h"
#include "core/Input.h"
#include "core/Window.h"

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

int length;

int main(void) {

	Window::init();
	Window::window(1920, 1080, "Hello World", WINDOWED);
	Window::initGL();

	//length = 0;
	DisplayMode* dmodes = Window::getAvailableDisplayModes(&length);
	cout << &length << endl;
	cout << length << endl; // the number of DMs is 22 on my screen, the value should be arround there, but the variable dosen't point right.

	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, Window::getWidth(), Window::getHeight());
	perspectiveGL(70, Window::aspectRatio(), 0.03f, 1000);
	glMatrixMode(GL_MODELVIEW);

	Input::mouseGrab(false);

	float ry = 0, rx = 0, zm = -4, time = 0;
	int i = 0;

	while (!Window::isCloseRequested()) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Input::update();

		glLoadIdentity();

		glTranslatef(0, 0, zm);
		time += 1.f;

		glRotatef(ry, 0, 1, 0);
		glRotatef(rx, cosf(ry * 3.141592653589f / 180), 0, sinf(ry * 3.141592653589f / 180));

		/* Sample Input */
		ry += 0.1f * Input::getMDX();
		rx += 0.1f * Input::getMDY();

		if (Input::event(MOUSE_WHEEL_UP))
			zm *= 1.1f;
		if (Input::event(MOUSE_WHEEL_DOWN))
			zm /= 1.1f;

		/* toggle through all the */
		if (Input::eventStarted(KEY_SPACE)) {
			DisplayMode dm = dmodes[i++ % length];
			cout << "Mode: " << dm.width << " x " << dm.height << endl;
			Window::window(&dm, "Hello World", WINDOWED);
			Window::initGL();
			glEnable(GL_DEPTH_TEST);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glViewport(0, 0, Window::getWidth(), Window::getHeight());
			perspectiveGL(70, Window::aspectRatio(), 0.03f, 1000);
			glMatrixMode(GL_MODELVIEW);
		}
		

		/*Sample Rendering */
		glBegin(GL_TRIANGLES);
		{
			glColor3f(0, 0, 1);
			glVertex3f(-1, -1, 1);
			glColor3f(0, 1, 0);
			glVertex3f(0, 1, 0);
			glColor3f(1, 0, 0);
			glVertex3f(1, -1, 1);

			glColor3f(1, 0, 0);
			glVertex3f(1, -1, 1);
			glColor3f(0, 1, 0);
			glVertex3f(0, 1, 0);
			glColor3f(0, 0, 1);
			glVertex3f(1, -1, -1);

			glColor3f(1, 0, 0);
			glVertex3f(-1, -1, -1);
			glColor3f(0, 1, 0);
			glVertex3f(0, 1, 0);
			glColor3f(0, 0, 1);
			glVertex3f(1, -1, -1);

			glColor3f(1, 0, 0);
			glVertex3f(-1, -1, -1);
			glColor3f(0, 1, 0);
			glVertex3f(0, 1, 0);
			glColor3f(0, 0, 1);
			glVertex3f(-1, -1, 1);
		}
		glEnd();
		glBegin(GL_QUADS);
		{
			glColor3f(1, 0, 0);
			glVertex3f(-1, -1, -1);
			glColor3f(0, 0, 1);
			glVertex3f(1, -1, -1);
			glColor3f(1, 0, 0);
			glVertex3f(1, -1, 1);
			glColor3f(0, 0, 1);
			glVertex3f(-1, -1, 1);
		}
		glEnd();

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
