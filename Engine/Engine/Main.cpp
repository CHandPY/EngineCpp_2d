#include <iostream>

using namespace std;

#include "test/Apple.h"

int main() {

	cout << "Hello World" << endl;
	cout << "Hello again, World" << endl;
	cout << "Hello World... yeah... its the third time..." << endl;
	cout << "Sory..." << endl;

	Apple a = Apple(Apple::RED);

	cout << a.getMsg() << endl;
	
	system("pause");

	return 0;
}