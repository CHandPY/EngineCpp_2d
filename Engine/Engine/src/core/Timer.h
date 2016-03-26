#pragma once

#include <iostream>

#include "System.h"
#include "Logger.h"

namespace engine {
	namespace core {

		class Timer {

		public:
			static void update();
			static float getDelta();
			static float getFPS();

			static void setLogFPS(bool log);

		private:
			static float time;
			static long lastTime;
			static float delta;
			static float fps, fpsC, accum, fpsP;
			static long lastFPS, localFr;
			static bool native_log_fps;

			static long getTimeS();
			static float calcDeltaS();
			static void updateFPS();

		};
	}
}
