#include "Timer.h"

long Timer::lastTime = 0;
float Timer::time = 0;
float Timer::delta = 0;
float Timer::fps = 0;
float Timer::fpsC = 0;
long Timer::lastFPS = 0;
bool Timer::native_log_fps = false;

void Timer::update() {
	delta = calcDeltaS() / TIME_RESOLUTION;
	if (delta < 0) delta = 0;
	time += delta;
	updateFPS();
}

float Timer::getDelta() {
	return delta;
}

float Timer::getFPS() {
	return fps;
}

void Timer::setLogFPS(bool log) {
	native_log_fps = log;
}

long Timer::getTimeS() {
	return System::time();
}

float Timer::calcDeltaS() {
	long timeS = getTimeS();
	float delta = (float) (timeS - lastTime);
	lastTime = timeS;
	return delta;
}

int reset_count;
void Timer::updateFPS() {
	if ((int) time > lastFPS) {
		fps = fpsC;
		if (native_log_fps)
			std::cout << fps << std::endl;
		fpsC = 0;
		lastFPS++;
	}
	fpsC++;
}
