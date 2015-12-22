#include "Window.h"

GLFWwindow* Window::w_window = NULL;
int Window::w_width = 0;
int Window::w_height = 0;
int Window::w_windowMode = 0;
const char* Window::w_title = "";

void Window::init() {
	if (!glfwInit())
		System::exit(1);
}

void Window::window(int width, int height, const char* title, int windowMode) {

	w_width = width;
	w_height = height;
	w_title = title;
	w_windowMode = windowMode;

	makeWindow();

	setInputCallbacks();

}

void Window::initGL() {
	glfwMakeContextCurrent(w_window);
}

void Window::update() {
	glfwSwapBuffers(w_window);
}

bool Window::isCloseRequested() {
	return glfwWindowShouldClose(w_window);
}

void Window::destroy() {
	glfwDestroyWindow(w_window);
}

void Window::end() {
	glfwTerminate();
}

void Window::setTitle(const char* title) {
	Window::w_title = title;
	glfwSetWindowTitle(Window::w_window, Window::w_title);
}

void Window::setCursorMode(int mode) {
	glfwSetInputMode(w_window, GLFW_CURSOR, mode);
}

void Window::setVideoMode(GLFWvidmode * mode) {

}

float Window::aspectRatio() {
	return w_width / (float) w_height;
}

int Window::getWidth() {
	return w_width;
}

int Window::getHeight() {
	return w_height;
}

void Window::makeWindow() {

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();

	if (w_windowMode == FULLSCREEN_WINDOWED) {
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		glfwWindowHint(GLFW_DECORATED, false);

		w_width = mode->width;
		w_height = mode->height;

		Window::w_window = glfwCreateWindow(w_width, w_height, w_title, NULL, NULL);
	} else {
		Window::w_window = glfwCreateWindow(Window::w_width, Window::w_height, Window::w_title, (w_windowMode) ? monitor : NULL, NULL);
	}

	if (!w_window) {
		end();
		System::exit(1);
	}

}

void Window::setInputCallbacks() {
	glfwSetScrollCallback(w_window, Input::scroll_callback);
	glfwSetKeyCallback(w_window, Input::key_callback);
	glfwSetMouseButtonCallback(w_window, Input::mouse_callback);
	glfwSetCursorPosCallback(w_window, Input::m_pos_callback);
}
