#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "IO.h"

char** IO::load(char *filepath, int *length) {
	FILE *fp = fopen(filepath, "r");
	char line[1024];
	//this reads one line
	while (fgets(line, 1023, fp));

	fclose(fp);
}