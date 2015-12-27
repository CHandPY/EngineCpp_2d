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

string System::str(char val) {
	return std::to_string(val);
}

string System::str(short val) {
	return std::to_string(val);
}

string System::str(int val) {
	return std::to_string(val);
}

string System::str(long val) {
	return std::to_string(val).append("L");
}

string System::str(long long val) {
	return std::to_string(val).append("L");
}

string System::str(unsigned long long val) {
	return std::to_string(val).append("L");
}

string System::str(float val) {
	return std::to_string(val).append("F");
}

string System::str(bool val) {
	return (val) ? string("true") : string("false");
}

string System::strhx(char val) {
	return strhx_internal(val, sizeof(char));
}

string System::strhx(short val) {
	return strhx_internal(val, sizeof(short));
}

string System::strhx(int val) {
	return strhx_internal(val, sizeof(int));
}

string System::strhx(long long val) {
	return strhx_internal(val, sizeof(long long));
}
string System::strhx(unsigned short val) {
	return strhx_internal(val, sizeof(short));
}

string System::strhx(unsigned int val) {
	return strhx_internal(val, sizeof(int));
}

string System::strhx(unsigned long long val) {
	return strhx_internal(val, sizeof(long long));
}

const char hexLetters[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
string System::strhx_internal(unsigned long long val, const int explicit_byte_size) {
	int size = 2 * explicit_byte_size;
	// format 0x(FF) -> byte ex: unsgned int = 0xFFFFFFFF
	int *bits = new int[size]; // creates the array for the value of each bit (0 .. explicit_size)

	for (int i = size - 1; i >= 0; i--) {
		int x = val % 16;
		val /= 16;
		bits[i] = x;
	}

	char *str = new char[2 + size + 1];
	str[0] = '0';
	str[1] = 'x';

	for (int i = 0; i < size; i++) {
		str[i + 2] = hexLetters[bits[i]];
	}
	str[size + 2] = '\0';

	return string(str);
}
