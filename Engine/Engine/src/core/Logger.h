#pragma once

namespace engine {

#define LOG_INTERNAL_CONSOLE 0x0

#if defined(_WIN32)

#include <iostream>
#include <Windows.h>

#define set_console_color(color) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color)

#define output_to_console(out) std::cout << out << std::endl

#elif defined(__APPLE__) && defined(__MACH__)

// SHOULD BE FIXED SOME DAY FOR OSX DEBUG AND COMPATIBILITY

#define set_console_color(color) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color)

#define output_to_console(out) std::cout << out << std::endl

#elif LOG_INTERNAL_CONSOLE

#endif

#define PRINT(log, color) set_console_color(color); output_to_console(log)

#define LOG(log) PRINT(log, 0x07)

#define ERR(log) PRINT(log, 0x0C)

#define WRN(log) PRINT(log, 0x0E)

#define PASS(log) PRINT(log, 0x0A)

}