#pragma once

#include <GLFW/glfw3.h>

#include "Input.h"
#include "System.h"

#define WINDOWED 0x00
#define FULLSCREEN 0x01
#define FULLSCREEN_WINDOWED 0x02

#define ASPECT_4_3 0x10
#define ASPECT_16_9 0x11
#define ASPECT_16_10 0x12
#define ASPECT_5_4 0x13
#define ASPECT_OTHER 0x14
#define ASPECT_ALL 0x15

struct DisplayMode {
	int width, height, ratioTag;
	float aspectRatio;

	DisplayMode();
	DisplayMode(int width, int height);
	
	DisplayMode* operator= (DisplayMode* mode);
};

class Window {

public:
	static void init();
	static void window(int width, int height, const char* title, int windowMode, bool vSync);
	static void window(DisplayMode* displayMode, const char* title, int windowMode, bool vSync);
	static void initGL();
	static void update();
	static bool isCloseRequested();
	static void destroy();
	static void end();

	static void setTitle(const char* title);
	static void setCursorMode(int mode);
	static void setVSync(bool vSync);
	static void setDisplayMode(DisplayMode* displayMode);
	static void setWindowMode(int windowMode);

	static void setUserWindowSetting(DisplayMode* displayMode, int videoMode, bool vSync);

	static float aspectRatio();
	static int getWidth();
	static int getHeight();

	static DisplayMode* getAvailableDisplayModes(int* count, int filter = ASPECT_ALL);

protected:
	static void makeWindow(GLFWmonitor* monitor_parrent);

private:
	static GLFWwindow* w_window;
	static DisplayMode* w_displayMode;
	static const char* w_title;
	static int w_windowMode;
	static bool w_vSync;

	static void setInputCallbacks();

};