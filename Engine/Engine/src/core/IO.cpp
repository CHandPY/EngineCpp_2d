#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "IO.h"

using namespace std;

string* IO::load(const char *filepath, int *length) {
	FILE *fp = fopen(filepath, "r");

	if (!fp) {
		cerr << "Failled to oppen file: " << filepath << endl;
		return 0;
	}
	
	vector<string> *lines = new vector<string>();

	char line[CHAR_AMT];
	while (fgets(line, 1023, fp)) {
		lines->push_back(string(line));
	}

	fclose(fp);

	*length = lines->size();

	return &(*lines)[0];
}