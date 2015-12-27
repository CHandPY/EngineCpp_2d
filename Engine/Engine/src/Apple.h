#pragma once

#include "core/ToString.h"

class Apple : ToString {

public:
	Apple(string name, int color, float radius, float roundness) : name(name), hex_color(color), radius(radius), roundness(roundness) {}

	string toString() { return "Apple: " + name + " of color: " + strhx(hex_color) + ". additional dev. info: { " + str(roundness) + ", " + str(radius) + " }.";  }

private:
	float radius, roundness;
	int hex_color;
	string name;

};