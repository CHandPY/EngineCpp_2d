#pragma once

#include <fstream>
#include <iostream>
#include <thread>
#include <GLFW/glfw3.h>

using namespace std;

#define SECONDS                     1
#define MILISECONDS                 1'000
#define NANOSECONDS                 10'000'000
#define TIME_RESOLUTION             NANOSECONDS

#define sys_seconds(system_time)    (TIME_RESOLUTION * system_time)
#define sys_milis(system_time)      (system_time / (float) (TIME_RESOLUTION / MILISECONDS))
#define sec_milis(time_seconds)     (MILISECONDS * time_seconds)

typedef long sys_time;
typedef float sys_secs;

namespace engine {
	namespace core {

		class System {

		public:
			static void exit(int code);
			static void curThreadSleep(long milis);

			static sys_time time();
			static sys_secs timeSec();

		};
	}
}
