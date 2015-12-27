#pragma once

#include <fstream>
#include <iostream>
#include <thread>
#include <string>
#include <GLFW\glfw3.h>

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

class System {

public:
	static void exit(int code);
	static void curThreadSleep(long milis);

	static sys_time time();
	static sys_secs timeSec();

	static string str(char val);
	static string str(short val);
	static string str(int val);
	static string str(long val);
	static string str(long long val);
	static string str(unsigned long long val);
	static string str(float val);
	static string str(bool val);

	static string strhx(char val);
	static string strhx(short val);
	static string strhx(int val);
	static string strhx(long long val);
	static string strhx(unsigned short val);
	static string strhx(unsigned int val);
	static string strhx(unsigned long long val);

private:
	inline static string strhx_internal(unsigned long long val, const int explicit_size);

};
