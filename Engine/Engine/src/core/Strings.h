#pragma once

#include <string>

using namespace std;

namespace strings {

	string str(char val);
	string str(short val);
	string str(int val);
	string str(long val);
	string str(long long val);
	string str(unsigned char val);
	string str(unsigned short val);
	string str(unsigned int val);
	string str(unsigned long val);
	string str(unsigned long long val);
	string str(float val);
	string str(double val);
	string str(bool val);

	string strhx(char val);
	string strhx(short val);
	string strhx(int val);
	string strhx(long long val);
	string strhx(unsigned short val);
	string strhx(unsigned int val);
	string strhx(unsigned long long val);

	const string nextline = "\n";

	namespace internal {
		inline string strhx_internal(unsigned long long val, const int explicit_size);
	}

}