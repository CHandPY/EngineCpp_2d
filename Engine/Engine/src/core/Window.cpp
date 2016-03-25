#include "Window.h"

#include <iostream>

namespace engine {
	namespace core {

		GLFWwindow* Window::w_window = NULL;
		DisplayMode* Window::w_displayMode = NULL;
		int Window::w_windowMode = 0;
		bool Window::w_vSync = false;
		const char* Window::w_title = "";

		void Window::init() {
			if (!glfwInit())
				System::exit(1);
		}

		void Window::window(int width, int height, const char* title, int windowMode, bool vSync) {
			Window::window(new DisplayMode(width, height), title, windowMode, vSync);
		}

		void Window::window(DisplayMode* displayMode, const char * title, int windowMode, bool vSync) {

			GLFWmonitor *mon = NULL;
			if (w_window) {
				mon = glfwGetWindowMonitor(w_window);
				destroy();
			}

			w_displayMode = displayMode;
			w_title = title;
			w_windowMode = windowMode;
			w_vSync = vSync;

			makeWindow(mon);

			setVSync(vSync);

			setInputCallbacks();
		}

		void Window::initGL() {
			glfwMakeContextCurrent(w_window);
			setVSync(w_vSync);
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

		void Window::setVSync(bool vSync) {
			glfwSwapInterval(0);
		}

		void Window::setDisplayMode(DisplayMode * displayMode) {
			Window::window(displayMode, w_title, w_windowMode, w_vSync);
		}

		void Window::setWindowMode(int windowMode) {
			Window::window(w_displayMode, w_title, windowMode, w_vSync);
		}

		void Window::setUserWindowSetting(DisplayMode * displayMode, int windowMode, bool vSync) {
			Window::window(displayMode, w_title, windowMode, vSync);
		}

		float Window::aspectRatio() {
			return w_displayMode->aspectRatio;
		}

		int Window::getWidth() {
			return w_displayMode->width;
		}

		int Window::getHeight() {
			return w_displayMode->height;
		}

		DisplayMode * Window::getAvailableDisplayModes(int* count, int filter) {
			GLFWmonitor* monitor = glfwGetWindowMonitor(w_window);
			monitor = (monitor) ? monitor : glfwGetPrimaryMonitor();
			int cnt, number_of_monitors = 0;
			const GLFWvidmode* modes_raw = glfwGetVideoModes(monitor, &cnt);
			DisplayMode *modes = new DisplayMode[cnt];
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);
			for (int i = 0; i < cnt; i++) {
				if (modes_raw[i].refreshRate == mode->refreshRate) {
					DisplayMode md(modes_raw[i].width, modes_raw[i].height);
					if (filter == ASPECT_ALL) {
						modes[number_of_monitors++] = md;
					} else if (md.ratioTag == filter) {
						modes[number_of_monitors++] = md;
					}
				}

			}
			*count = number_of_monitors;
			return modes;
		}

		void Window::makeWindow(GLFWmonitor* monitor_parrent) {

			GLFWmonitor* monitor = (monitor_parrent) ? monitor_parrent : glfwGetPrimaryMonitor();

			if (w_windowMode == FULLSCREEN_WINDOWED) {
				const GLFWvidmode* mode = glfwGetVideoMode(monitor);

				glfwWindowHint(GLFW_RED_BITS, mode->redBits);
				glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
				glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
				glfwWindowHint(GLFW_DECORATED, false);

				w_displayMode = new DisplayMode(mode->width, mode->height);

				Window::w_window = glfwCreateWindow(w_displayMode->width, w_displayMode->height, w_title, NULL, NULL);
			} else {
				glfwWindowHint(GLFW_DECORATED, true);
				Window::w_window = glfwCreateWindow(w_displayMode->width, w_displayMode->height, w_title, (w_windowMode) ? monitor : NULL, NULL);
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

		DisplayMode::DisplayMode() {}

		DisplayMode::DisplayMode(int width, int height) : width(width), height(height) {
			aspectRatio = width / (float) height;
			if (aspectRatio == (4.f / 3.f))
				ratioTag = ASPECT_4_3;
			else if (aspectRatio == (16.f / 9.f))
				ratioTag = ASPECT_16_9;
			else if (aspectRatio == (16.f / 10.f))
				ratioTag = ASPECT_16_10;
			else if (aspectRatio == (5.f / 4.f))
				ratioTag = ASPECT_5_4;
			else
				ratioTag = ASPECT_OTHER;
		}

		DisplayMode * DisplayMode::operator=(DisplayMode * mode) {
			width = mode->width;
			height = mode->height;
			ratioTag = mode->ratioTag;
			aspectRatio = mode->aspectRatio;
			return this;
		}
	}
}
