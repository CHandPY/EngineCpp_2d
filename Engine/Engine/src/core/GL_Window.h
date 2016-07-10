#pragma once

#include "Window.h"
#include "System.h"
#include "Logger.h"

#include <GLFW/glfw3.h>

namespace engine {
	namespace core {
		namespace GL {

			class GL_Window : public Window {

			public:
				GL_Window(const DisplayMode & displayMode, const char * title);

				virtual void create();
				virtual void update() const;
				virtual bool isCloseRequested() const;
				virtual void destroy();

				void setDisplayMode(DisplayMode& newMode);
				void setTitle(const char* title);

				virtual DisplayMode* getAvalableDisplayModes(int * count, int filter, int winMode = WINDOWED, bool vSync = false) const;
				virtual int* getSupportedWindowModes(int * count) const;

				void attachInput(Input * i);

				/* input callbacks */
				static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
				static void mouse_callback(GLFWwindow* window, int button, int action, int mods);
				static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
				static void m_pos_callback(GLFWwindow* window, double xpos, double ypos);

			private:
				GLFWwindow * m_window;

				static Input * s_input;

				void make_window_internal(GLFWmonitor * monitor_parent);

			};

		}
	}
}