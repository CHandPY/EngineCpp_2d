#pragma once

#include <string>


namespace engine {
	namespace core {
		namespace strings {
			
			std::string str(char val);
			std::string str(short val);
			std::string str(int val);
			std::string str(long val);
			std::string str(long long val);
			std::string str(unsigned char val);
			std::string str(unsigned short val);
			std::string str(unsigned int val);
			std::string str(unsigned long val);
			std::string str(unsigned long long val);
			std::string str(float val);
			std::string str(double val);
			std::string str(bool val);

			std::string strhx(char val);
			std::string strhx(short val);
			std::string strhx(int val);
			std::string strhx(long long val);
			std::string strhx(unsigned short val);
			std::string strhx(unsigned int val);
			std::string strhx(unsigned long long val);

			const std::string nextline = "\n";

			namespace internal {
				inline std::string strhx_internal(unsigned long long val, const int explicit_size);
			}

		}
	}
}