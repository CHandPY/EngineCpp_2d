#pragma once

#include <GLFW/glfw3.h>

#include "Input.h"
#include "System.h"

#define WINDOWED 0x0
#define FULLSCREEN 0x1
#define FULLSCREEN_WINDOWED 0x2

class Window {

public:
	static void init();
	static void window(int width, int height, const char* title, int windowMode);
	static void initGL();
	static void update();
	static bool isCloseRequested();
	static void destroy();
	static void end();

	static void setTitle(const char* title);
	static void setCursorMode(int mode);
	static void setVideoMode(GLFWvidmode* mode);

	static float aspectRatio();
	static int getWidth();
	static int getHeight();

protected:
	static void makeWindow();

private:
	static GLFWwindow* w_window;
	static int w_width, w_height;
	static const char* w_title;
	static int w_windowMode;

	static void setInputCallbacks();

};