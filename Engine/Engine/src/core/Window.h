#pragma once

#include <GLFW/glfw3.h>

#include "Input.h"
#include "System.h"

#define WINDOWED            0x00
#define FULLSCREEN          0x01
#define FULLSCREEN_WINDOWED 0x02

#define ASPECT_4_3          0x10
#define ASPECT_16_9         0x11
#define ASPECT_16_10        0x12

#define ASPECT_5_4          0x13
#define ASPECT_OTHER        0x14
#define ASPECT_ALL          0x15

namespace engine {
	namespace core {

		// probably add vSync + WindowMode and keep in parent (as is)
		struct DisplayMode {
			int width, height, ratioTag;
			float aspectRatio;

			DisplayMode();
			DisplayMode(int width, int height);

			DisplayMode* operator= (DisplayMode* mode);
		};

		class Window {

		public:
			static void init(); // should merge into windowCreator
			static void window(int width, int height, const char* title, int windowMode, bool vSync); // - static -> self
			static void window(DisplayMode* displayMode, const char* title, int windowMode, bool vSync); // ^^ + change * -> &
			static void initGL(); // rem : move to engine ?
			static void update(); // - static
			static bool isCloseRequested(); // - static
			static void destroy(); // to destructor ?
			static void end(); // + static : move elsewhere ? (engine master class)

			static void setTitle(const char* title); // - static
			static void setCursorMode(int mode); // - static : maybe move ?
			static void setVSync(bool vSync); // merge to DisplayMode
			static void setDisplayMode(DisplayMode* displayMode); // - static
			static void setWindowMode(int windowMode); // - static : merge to DisplayMode?

			static void setUserWindowSetting(DisplayMode* displayMode, int videoMode, bool vSync); // becomes set display mode

			static float aspectRatio(); // can get from DM : rep wt getDM()
			static int getWidth(); // ^^
			static int getHeight(); // ^^

			static DisplayMode* getAvailableDisplayModes(int* count, int filter = ASPECT_ALL); // keep : maybe - static

		protected:
			static void makeWindow(GLFWmonitor* monitor_parrent); // move to child : too specific to GLFW

		private:
			// remove all attribs (except DM not sure yet... i mean, it kinda makes sence in the parent since all windows have one)
			static GLFWwindow* w_window;
			static DisplayMode* w_displayMode;
			static const char* w_title;
			static int w_windowMode;
			static bool w_vSync;

			// probably move to engine core, other systems might regard it as engine and not window.
			static void setInputCallbacks();

		};

	}
}