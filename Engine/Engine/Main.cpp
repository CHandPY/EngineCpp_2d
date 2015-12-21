#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>

using namespace std;

#include "core/System.h"
#include "core/Input.h"
#include "core/Window.h"

void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar);

int main(void) {

	Window::init(1920, 1080, "Hello World", 0);
	Window::initGL();

	/* Get the Video Modes (DisplayModes)
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	int count;
	const GLFWvidmode* modes = glfwGetVideoModes(monitor, &count);
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	for (int i = 0; i < count; i++) {
		if (modes[i].refreshRate == mode->refreshRate)
			cout << "Mode: " << modes[i].width << " x " << modes[i].height << " @" << modes[i].refreshRate << "Hz" << endl;
	}
	*/

	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	perspectiveGL(70, 1920 / 1080.f, 0.03f, 1000);
	glMatrixMode(GL_MODELVIEW);

	Input::mouseGrab(false);

	float ry = 0, rx = 0, zm = -4, time = 0;

	while (!Window::isCloseRequested()) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Input::update();

		glLoadIdentity();

		glTranslatef(0, 0, zm);
		time += 1.f;

		glRotatef(ry, 0, 1, 0);
		glRotatef(rx, cosf(ry * 3.141592653589 / 180), 0, sinf(ry * 3.141592653589 / 180));

		/* Sample Input */
		if (Input::event(MOUSE_1)) {
			ry += 0.1f * Input::getMDX();
			rx += 0.1f * Input::getMDY();
		}

		if (Input::event(MOUSE_WHEEL_UP))
			zm *= 1.1f;
		if (Input::event(MOUSE_WHEEL_DOWN))
			zm /= 1.1f;

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
