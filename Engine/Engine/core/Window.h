#pragma once

#include <GLFW/glfw3.h>

#include "Input.h"
#include "System.h"

class Window {

public:
	static void init(int width, int height, const char* title, bool fullscreen);
	static void initGL();
	static void update();
	static bool isCloseRequested();
	static void destroy();
	static void end();

	static void setTitle(const char* title);
	static void setCursorMode(int mode);

private:
	static GLFWwindow* w_window;
	static int w_width, w_height;
	static const char* w_title;
	static bool w_fullscreen;

	static void setInputCallbacks();

};