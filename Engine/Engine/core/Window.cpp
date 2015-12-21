#include "Window.h"

GLFWwindow* Window::w_window = NULL;
int Window::w_width = 0;
int Window::w_height = 0;
bool Window::w_fullscreen = false;
const char* Window::w_title = "";

void Window::init(int width, int height, const char* title, bool fullscreen) {

	if (!glfwInit())
		System::exit(1);

	Window::w_width = width;
	Window::w_height = height;
	Window::w_title = title;

	Window::w_window = glfwCreateWindow(Window::w_width, Window::w_height, Window::w_title, NULL, NULL);

	if (!w_window) {
		end();
		System::exit(1);
	}

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

void Window::setInputCallbacks() {
	glfwSetScrollCallback(w_window, Input::scroll_callback);
	glfwSetKeyCallback(w_window, Input::key_callback);
	glfwSetMouseButtonCallback(w_window, Input::mouse_callback);
	glfwSetCursorPosCallback(w_window, Input::m_pos_callback);
}
