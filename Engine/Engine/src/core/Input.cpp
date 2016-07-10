#include "Input.h"

namespace engine {
	namespace core {

		Input::Input() {
		}

		Input::~Input() {
			delete[] events;
			delete[] events_started;
			delete[] events_stopped;
			delete[] events_repeat;
		}

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
				;//Window::setCursorMode(GLFW_CURSOR_DISABLED);
			else
				;//Window::setCursorMode(GLFW_CURSOR_NORMAL);
		}

		bool Input::mouseGrabed() {
			return m_grab;
		}
	}
}
