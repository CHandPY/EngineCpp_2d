#include "Window.h"

namespace engine {
	namespace core {

		DisplayMode::DisplayMode() : DisplayMode(0, 0) {}

		DisplayMode::DisplayMode(int width, int height, int winMode, bool vSync) 
			: width(width), height(height), winMode(winMode), vSync(vSync) 
		{
			aspectRatio = width / (float) height;
			if (aspectRatio == (4.f / 3.f))
				ratioTag = ASPECT_4_3;
			else if (aspectRatio == (16.f / 9.f))
				ratioTag = ASPECT_16_9;
			else if (aspectRatio == (16.f / 10.f))
				ratioTag = ASPECT_16_10;
			else if (aspectRatio == (5.f / 4.f))
				ratioTag = ASPECT_5_4;
			else
				ratioTag = ASPECT_OTHER;
		}

		DisplayMode& DisplayMode::operator= (const DisplayMode& other) {
			width = other.width;
			height = other.height;
			winMode = other.winMode;
			vSync = other.vSync;
			aspectRatio = other.aspectRatio;
			ratioTag = other.ratioTag;
			return *this;
		}

		bool DisplayMode::isVSyncOnlyChange(DisplayMode& other) const {
			return vSync != other.vSync && (width == other.width && height == other.height && winMode == other.winMode);
		}

		Window::Window(const DisplayMode & displayMode, const char * title) 
			: m_title(title)
		{ 
			m_displayMode = new DisplayMode();
			*m_displayMode = displayMode;
		}

		Window::~Window() { }

		void Window::setDisplayMode(const DisplayMode& newMode) {
			*m_displayMode = newMode;
		}

		DisplayMode& Window::getDisplayMode() const {
			return *m_displayMode;
		}

		void Window::setTitle(const char * title) {
			m_title = title;
		}

		const char * Window::getTitle() const {
			return m_title;
		}

		Input * Window::getInput() const {
			return m_input;
		}

		void Window::attachInput(Input * i) {
			this->m_input = i;
		}

	}
}