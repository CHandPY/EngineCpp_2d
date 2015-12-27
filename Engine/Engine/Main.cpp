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

int length;

int main() {

	Apple a = Apple("Boby", 0xffffaa00, 7.2, 0.0221);

	cout << a.toString() << endl;

	Window::init();
	Window::window(1920, 1080, "Hello World", FULLSCREEN);
	Window::initGL();

	glfwSwapInterval(0);

	Timer::setLogFPS(true);

	//length = 0;
	DisplayMode* dmodes = Window::getAvailableDisplayModes(&length);

	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, Window::getWidth(), Window::getHeight());
	perspectiveGL(70, Window::aspectRatio(), 0.03f, 1000);
	glMatrixMode(GL_MODELVIEW);

	Input::mouseGrab(true);

	float ry = 0, rx = 0, zm = -4, time = 0;
	int i = 0;

	bool fps_flag = false;

	while (!Window::isCloseRequested()) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Timer::update();
		Input::update();

		glLoadIdentity();

		glTranslatef(0, 0, zm);
		time += 1.f;

		glRotatef(ry, 0, 1, 0);
		glRotatef(rx, cosf(ry * 3.141592653589f / 180), 0, sinf(ry * 3.141592653589f / 180));

		/* Sample Input */
		ry += 0.1f * Input::getMDX();
		rx += 0.1f * Input::getMDY();

		//cout << "(" << Input::getMDX() << ", " << Input::getMDY() << ")" << endl;

		if (Input::event(MOUSE_WHEEL_UP))
			zm *= 1.1f;
		if (Input::event(MOUSE_WHEEL_DOWN))
			zm /= 1.1f;

		if (Input::eventStarted(KEY_ESCAPE)) {
			Input::mouseGrab(false);
		}

		if (Input::eventStarted(MOUSE_1)) {
			Input::mouseGrab(true);
		}

		/* toggle through all the */
		if (Input::eventStarted(KEY_SPACE)) {
			DisplayMode dm = dmodes[i++ % length];
			cout << "Mode: " << dm.width << " x " << dm.height << endl;
			Window::window(&dm, "Hello World", FULLSCREEN);
			Window::initGL();
			glEnable(GL_DEPTH_TEST);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glViewport(0, 0, Window::getWidth(), Window::getHeight());
			perspectiveGL(70, Window::aspectRatio(), 0.03f, 1000);
			glMatrixMode(GL_MODELVIEW);
		}
		

		/*Sample Rendering */
		int l = 200;
		for (int i = 0; i < l * l; i++) {
			glPushMatrix();
			glTranslatef(0, i / l - (l / 2), i % l - (l / 2));
			glScalef(.4f, .4f, .4f);
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
			glPopMatrix();
		}

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
