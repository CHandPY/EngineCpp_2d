#pragma once

#include <GLFW/glfw3.h>

#include "Window.h"

/* unknown input event */
#define UNKNOWN_EVENT          -1

/* Printable keys */
#define KEY_SPACE              32
#define KEY_APOSTROPHE         39  /* ' */
#define KEY_COMMA              44  /* , */
#define KEY_MINUS              45  /* - */
#define KEY_PERIOD             46  /* . */
#define KEY_SLASH              47  /* / */
#define KEY_0                  48
#define KEY_1                  49
#define KEY_2                  50
#define KEY_3                  51
#define KEY_4                  52
#define KEY_5                  53
#define KEY_6                  54
#define KEY_7                  55
#define KEY_8                  56
#define KEY_9                  57
#define KEY_SEMICOLON          59  /* ; */
#define KEY_EQUAL              61  /* = */
#define KEY_A                  65
#define KEY_B                  66
#define KEY_C                  67
#define KEY_D                  68
#define KEY_E                  69
#define KEY_F                  70
#define KEY_G                  71
#define KEY_H                  72
#define KEY_I                  73
#define KEY_J                  74
#define KEY_K                  75
#define KEY_L                  76
#define KEY_M                  77
#define KEY_N                  78
#define KEY_O                  79
#define KEY_P                  80
#define KEY_Q                  81
#define KEY_R                  82
#define KEY_S                  83
#define KEY_T                  84
#define KEY_U                  85
#define KEY_V                  86
#define KEY_W                  87
#define KEY_X                  88
#define KEY_Y                  89
#define KEY_Z                  90
#define KEY_LEFT_BRACKET       91  /* [ */
#define KEY_BACKSLASH          92  /* \ */
#define KEY_RIGHT_BRACKET      93  /* ] */
#define KEY_GRAVE_ACCENT       96  /* ` */
#define KEY_WORLD_1            161 /* non-US #1 */
#define KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define KEY_ESCAPE             256
#define KEY_ENTER              257
#define KEY_TAB                258
#define KEY_BACKSPACE          259
#define KEY_INSERT             260
#define KEY_DELETE             261
#define KEY_RIGHT              262
#define KEY_LEFT               263
#define KEY_DOWN               264
#define KEY_UP                 265
#define KEY_PAGE_UP            266
#define KEY_PAGE_DOWN          267
#define KEY_HOME               268
#define KEY_END                269
#define KEY_CAPS_LOCK          280
#define KEY_SCROLL_LOCK        281
#define KEY_NUM_LOCK           282
#define KEY_PRINT_SCREEN       283
#define KEY_PAUSE              284
#define KEY_F1                 290
#define KEY_F2                 291
#define KEY_F3                 292
#define KEY_F4                 293
#define KEY_F5                 294
#define KEY_F6                 295
#define KEY_F7                 296
#define KEY_F8                 297
#define KEY_F9                 298
#define KEY_F10                299
#define KEY_F11                300
#define KEY_F12                301
#define KEY_F13                302
#define KEY_F14                303
#define KEY_F15                304
#define KEY_F16                305
#define KEY_F17                306
#define KEY_F18                307
#define KEY_F19                308
#define KEY_F20                309
#define KEY_F21                310
#define KEY_F22                311
#define KEY_F23                312
#define KEY_F24                313
#define KEY_F25                314
#define KEY_KP_0               320
#define KEY_KP_1               321
#define KEY_KP_2               322
#define KEY_KP_3               323
#define KEY_KP_4               324
#define KEY_KP_5               325
#define KEY_KP_6               326
#define KEY_KP_7               327
#define KEY_KP_8               328
#define KEY_KP_9               329
#define KEY_KP_DECIMAL         330
#define KEY_KP_DIVIDE          331
#define KEY_KP_MULTIPLY        332
#define KEY_KP_SUBTRACT        333
#define KEY_KP_ADD             334
#define KEY_KP_ENTER           335
#define KEY_KP_EQUAL           336
#define KEY_LEFT_SHIFT         340
#define KEY_LEFT_CONTROL       341
#define KEY_LEFT_ALT           342
#define KEY_LEFT_SUPER         343
#define KEY_RIGHT_SHIFT        344
#define KEY_RIGHT_CONTROL      345
#define KEY_RIGHT_ALT          346
#define KEY_RIGHT_SUPER        347
#define KEY_MENU               348
#define KEY_LAST               KEY_MENU

/* Mouse buttons */
#define MOUSE_1                KEY_LAST + 1
#define MOUSE_2                MOUSE_1 + 1
#define MOUSE_3                MOUSE_1 + 2
#define MOUSE_4                MOUSE_1 + 3
#define MOUSE_5                MOUSE_1 + 4
#define MOUSE_6                MOUSE_1 + 5
#define MOUSE_7                MOUSE_1 + 6
#define MOUSE_8                MOUSE_1 + 7
#define MOUSE_BUTTON_LAST      MOUSE_8

/* Mouse wheel */
#define MOUSE_WHEEL_UP         MOUSE_BUTTON_LAST + 1
#define MOUSE_WHEEL_DOWN       MOUSE_WHEEL_UP + 1

/* the max number of events */
#define LAST_EVENT_BOUND       512

/* Event actions */
#define RELEASE                0
#define PRESS                  1
#define REPEAT                 2

namespace engine {
	namespace core {

		class Input {

		public:
			static int event(int id);
			static int eventStarted(int id);
			static int eventStopped(int id);
			static int getMX();
			static int getMY();
			static int getMDX();
			static int getMDY();
			static void update();
			static void mouseGrab(bool grab);

			static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			static void mouse_callback(GLFWwindow* window, int button, int action, int mods);
			static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
			static void m_pos_callback(GLFWwindow* window, double xpos, double ypos);

			static bool mouseGrabed();

		private:
			static int events[LAST_EVENT_BOUND];
			static int events_started[LAST_EVENT_BOUND];
			static int events_stopped[LAST_EVENT_BOUND];
			static int events_repeat[LAST_EVENT_BOUND]; // support for key_repeat? don't know if its worth it.
			static int MX, MY, DX, DY;
			static bool m_grab;

		};
	}
}