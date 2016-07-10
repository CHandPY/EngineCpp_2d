#include "GL_Window.h"

namespace engine {
	namespace core {
		namespace GL {

			Input * GL_Window::s_input = NULL;

			GL_Window::GL_Window(const DisplayMode & displayMode, const char * title) : Window(displayMode, title) {
			}

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

			void GL_Window::attachInput(Input * i) {
				Window::attachInput(i);
				s_input = m_input;
				glfwSetScrollCallback(m_window, scroll_callback);
				glfwSetKeyCallback(m_window, key_callback);
				glfwSetMouseButtonCallback(m_window, mouse_callback);
				glfwSetCursorPosCallback(m_window, m_pos_callback);
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

				glfwMakeContextCurrent(m_window);

			}

			void GL_Window::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods) {
				LOG((char) key);
				if (key == UNKNOWN_EVENT) return;

				if (action == PRESS) {
					s_input->events[key] = 1;
					s_input->events_started[key] = 1;
				}

				if (action == RELEASE) {
					s_input->events[key] = 0;
					s_input->events_stopped[key] = 1;
				}

				if (action == REPEAT) {
				}
			}

			void GL_Window::mouse_callback(GLFWwindow * window, int button, int action, int mods) {
				if (button == UNKNOWN_EVENT) return;

				button += MOUSE_1;

				if (action == PRESS) {
					s_input->events[button] = 1;
					s_input->events_started[button] = 1;
				}

				if (action == RELEASE) {
					s_input->events[button] = 0;
					s_input->events_stopped[button] = 1;
				}

				if (action == REPEAT) {
				}
			}

			void GL_Window::scroll_callback(GLFWwindow * window, double xoffset, double yoffset) {
				if (yoffset > 0) {
					s_input->events_started[MOUSE_WHEEL_UP] = (int) yoffset;
					s_input->events[MOUSE_WHEEL_UP] = (int) yoffset;
				} else {
					s_input->events_started[MOUSE_WHEEL_DOWN] = (int) yoffset;
					s_input->events[MOUSE_WHEEL_DOWN] = (int) yoffset;
				}

			}

			void GL_Window::m_pos_callback(GLFWwindow * window, double xpos, double ypos) {

				s_input->DX = (int) xpos - s_input->MX;
				s_input->DY = (int) ypos - s_input->MY;

				s_input->MX = (int) xpos;
				s_input->MY = (int) ypos;
			}

		}
	}
}