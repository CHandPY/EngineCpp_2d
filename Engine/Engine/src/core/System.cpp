#include "System.h"

void System::exit(int code) {
	std::exit(code);
}

void System::curThreadSleep(long milis) {
	std::this_thread::sleep_for(std::chrono::milliseconds(milis));
}

long System::time() {
	return glfwGetTime() * TIME_RESOLUTION;
}

sys_secs System::timeSec() {
	return glfwGetTime();
}
