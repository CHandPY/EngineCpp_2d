#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "lodepng.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define CHAR_AMT 1024

namespace engine {
	namespace core {

		using namespace std;

		class IO {

		public:
			static string* load(const char *filepath, int *length);
			static string load(const char *filepath);

			static unsigned char * loadPNG(unsigned& width, unsigned& height, char *filepath);

		};
	}
}
