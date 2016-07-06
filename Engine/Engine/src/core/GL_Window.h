#pragma once

#include "Window.h"

#include <GLFW/glfw3.h>

#include "Input.h"
#include "System.h"

namespace engine {
	namespace core {
		namespace GL {

			class GL_Window : public Window {

			public:
				virtual void create();
				virtual void update() const;
				virtual bool isCloseRequested() const;
				virtual void destroy();

				void setDisplayMode(DisplayMode& newMode);
				void setTitle(const char* title);

				virtual DisplayMode* getAvalableDisplayModes(int * count, int filter, int winMode = WINDOWED, bool vSync = false) const;
				virtual int* getSupportedWindowModes(int * count) const;

			private:
				GLFWwindow * m_window;

				void make_window_internal(GLFWmonitor * monitor_parent);

			};

		}
	}
}