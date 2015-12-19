#pragma once

class Apple {
public:
	enum Color
	{
		RED = 0, YELLOW, GREEN, BROWN
	};

	Apple(Color c);

	const char* getMsg() {

		switch (color) {
		case 0: return "OHHHHHHH ITS SOOOOO REEEDDDDD";
		case 1: return "ouuhhhh an automn apple";
		case 2: return "GREEN!! My favorites!!";
		case 3: return "Put that down its fucking rotten us twat!";
		default: return "wtf is this color";
		}
	}

private:
	Color color;
};