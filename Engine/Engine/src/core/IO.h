#pragma once

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <vector>
#include <string>

#include "lodepng.h"

#define CHAR_AMT 1024

namespace engine {
	namespace core {

		class IO {

		public:
			static std::string* load(const char *filepath, int *length);
			static std::string load(const char *filepath);

			static unsigned char * loadPNG(unsigned& width, unsigned& height, char *filepath);

		};
	}
}
