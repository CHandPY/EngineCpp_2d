#include "Input.h"

#include <iostream>

namespace engine {
	namespace core {

		int Input::events[LAST_EVENT_BOUND];
		int Input::events_started[LAST_EVENT_BOUND];
		int Input::events_stopped[LAST_EVENT_BOUND];
		int Input::DX = 0, Input::DY = 0, Input::MX = 0, Input::MY = 0;
		bool Input::m_grab = false;

		int Input::event(int id) {
			return events[id];
		}

		int Input::eventStarted(int id) {
			return events_started[id];
		}

		int Input::eventStopped(int id) {
			return events_stopped[id];
		}

		int Input::getMX() {
			return MX;
		}

		int Input::getMY() {
			return MY;
		}

		int Input::getMDX() {
			return DX;
		}

		int Input::getMDY() {
			return DY;
		}

		void Input::update() {

			//resset the key buffers that need resetting.
			memset(events_started, 0, sizeof(events));
			memset(events_stopped, 0, sizeof(events));
			events[MOUSE_WHEEL_UP] = 0;
			events[MOUSE_WHEEL_DOWN] = 0;

			DX = 0;
			DY = 0;

			glfwPollEvents();
		}

		void Input::mouseGrab(bool grab) {
			m_grab = grab;
			if (grab)
				Window::setCursorMode(GLFW_CURSOR_DISABLED);
			else
				Window::setCursorMode(GLFW_CURSOR_NORMAL);
		}

		void Input::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods) {
			if (key == UNKNOWN_EVENT) return;

			if (action == PRESS) {
				events[key] = 1;
				events_started[key] = 1;
			}

			if (action == RELEASE) {
				events[key] = 0;
				events_stopped[key] = 1;
			}

			if (action == REPEAT) {
			}
		}

		void Input::mouse_callback(GLFWwindow * window, int button, int action, int mods) {
			if (button == UNKNOWN_EVENT) return;

			button += MOUSE_1;

			if (action == PRESS) {
				events[button] = 1;
				events_started[button] = 1;
			}

			if (action == RELEASE) {
				events[button] = 0;
				events_stopped[button] = 1;
			}

			if (action == REPEAT) {
			}
		}

		void Input::scroll_callback(GLFWwindow * window, double xoffset, double yoffset) {
			if (yoffset > 0) {
				events_started[MOUSE_WHEEL_UP] = (int) yoffset;
				events[MOUSE_WHEEL_UP] = (int) yoffset;
			} else {
				events_started[MOUSE_WHEEL_DOWN] = (int) yoffset;
				events[MOUSE_WHEEL_DOWN] = (int) yoffset;
			}

		}

		void Input::m_pos_callback(GLFWwindow * window, double xpos, double ypos) {

			DX = (int) xpos - MX;
			DY = (int) ypos - MY;

			MX = (int) xpos;
			MY = (int) ypos;
		}

		bool Input::mouseGrabed() {
			return m_grab;
		}
	}
}
