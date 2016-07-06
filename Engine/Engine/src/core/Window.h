#pragma once

#define WINDOWED              0x00
#define FULLSCREEN            0x01
#define FULLSCREEN_WINDOWED   0x02

#define ASPECT_4_3            0x10
#define ASPECT_16_9           0x11
#define ASPECT_16_10          0x12

#define ASPECT_5_4            0x13
#define ASPECT_OTHER          0x14
#define ASPECT_ALL            0x15

namespace engine {
	namespace core {

		struct DisplayMode {
			int width, height, ratioTag, winMode, vSync;
			float aspectRatio;

			DisplayMode();
			DisplayMode(int width, int height, int winMode = WINDOWED, bool vSync = false);
		
			DisplayMode& operator= (const DisplayMode& other);

			bool isVSyncOnlyChange(DisplayMode& other) const;
		};

		class Window {

			/* window pool system ? + focus check ?? */

		public:
			Window(const DisplayMode & displayMode, const char * title = "");
			virtual ~Window() = 0;

			virtual void create() = 0; // maybe const
			virtual void update() const = 0; // maybe not const
			virtual bool isCloseRequested() const = 0;
			virtual void destroy() = 0;
			
			/* Designed to be overiden to add functionality */
			void setDisplayMode(const DisplayMode const& newMode);
			DisplayMode& getDisplayMode() const;

			/* Designed to be overiden to add functionality */
			void setTitle(const char* title);
			const char * getTitle() const;

			virtual DisplayMode* getAvalableDisplayModes(int * count, int filter = ASPECT_ALL, int winMode = WINDOWED, bool vSync = false) const = 0;
			virtual int* getSupportedWindowModes(int * count) const = 0;

		protected:
			DisplayMode * m_displayMode;
			const char * m_title;

		};

	}
}