#include "GL_Window.h"

namespace engine {
	namespace core {
		namespace GL {
			
			void GL_Window::create() {

				GLFWmonitor *mon = NULL;
				if (m_window) {
					mon = glfwGetWindowMonitor(m_window);
					destroy();
				}

				make_window_internal(mon);

				// return new GL_Context(); // inits the context with the window or something 

			}

			void GL_Window::update() const {
				glfwSwapBuffers(m_window);
			}

			bool GL_Window::isCloseRequested() const {
				return glfwWindowShouldClose(m_window);
			}

			void GL_Window::destroy() {
				if (m_window)
					glfwDestroyWindow(m_window);
				glfwTerminate();
			}

			void GL_Window::setDisplayMode(DisplayMode& newMode) {
				Window::setDisplayMode(newMode);
				// if rebuild
				//     do rebuild
				// // no else, aply anyways //
				// apply vSync
				if (m_displayMode->isVSyncOnlyChange(newMode)) {

				} 

			}

			void GL_Window::setTitle(const char* title) {
				Window::setTitle(title);
				glfwSetWindowTitle(m_window, title);
			}

			DisplayMode * GL_Window::getAvalableDisplayModes(int * count, int filter, int winMode, bool vSync) const {
				GLFWmonitor* monitor = glfwGetWindowMonitor(m_window);
				monitor = (monitor) ? monitor : glfwGetPrimaryMonitor();
				int cnt, number_of_monitors = 0;
				const GLFWvidmode* modes_raw = glfwGetVideoModes(monitor, &cnt);
				DisplayMode *modes = new DisplayMode[cnt];
				const GLFWvidmode* mode = glfwGetVideoMode(monitor);
				for (int i = 0; i < cnt; i++) {
					if (modes_raw[i].refreshRate == mode->refreshRate) {
						DisplayMode md(modes_raw[i].width, modes_raw[i].height, winMode, vSync);
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

			int * GL_Window::getSupportedWindowModes(int * count) const {
				*count = 3;
				return new int[3] { WINDOWED, FULLSCREEN, FULLSCREEN_WINDOWED };
			}

			void GL_Window::make_window_internal(GLFWmonitor* monitor_parrent) {

				GLFWmonitor* monitor = (monitor_parrent) ? monitor_parrent : glfwGetPrimaryMonitor();

				if (m_displayMode->winMode == FULLSCREEN_WINDOWED) {
					const GLFWvidmode* mode = glfwGetVideoMode(monitor);

					glfwWindowHint(GLFW_RED_BITS, mode->redBits);
					glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
					glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
					glfwWindowHint(GLFW_DECORATED, false);

					m_displayMode = new DisplayMode(mode->width, mode->height, FULLSCREEN_WINDOWED, m_displayMode->vSync);

					m_window = glfwCreateWindow(m_displayMode->width, m_displayMode->height, m_title, NULL, NULL);
				} else {
					glfwWindowHint(GLFW_DECORATED, true);
					m_window = glfwCreateWindow(m_displayMode->width, m_displayMode->height, m_title, (m_displayMode->winMode) ? monitor : NULL, NULL);
				}

				if (!m_window) {
					destroy();
					System::exit(1);
				}

			}

		}
	}
}