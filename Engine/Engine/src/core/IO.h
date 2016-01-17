#pragma once

#define CHAR_AMT 1024

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class IO {

public:
	static string* load(const char *filepath, int *length);

};