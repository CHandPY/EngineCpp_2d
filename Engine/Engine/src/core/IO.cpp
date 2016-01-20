#include "IO.h"

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

unsigned char * IO::loadPNG(unsigned& width, unsigned& height, char * filepath) {
	std::vector<unsigned char> image;
	unsigned error = lodepng::decode(image, width, height, filepath);
	cout << error << endl;

	unsigned char *imageFix = new unsigned char[image.size()];
	int mod = sizeof(unsigned char);
	int side = int(sqrtf(image.size() / 4));

	int cnt = 0;
	for (int y = side - 1; y >= 0; y--) {
		for (int x = 0; x < side; x++) {
			imageFix[(x + (y * side)) * 4 + 0] = image[cnt++];
			imageFix[(x + (y * side)) * 4 + 1] = image[cnt++];
			imageFix[(x + (y * side)) * 4 + 2] = image[cnt++];
			imageFix[(x + (y * side)) * 4 + 3] = image[cnt++];
		}
	}

	return imageFix;

}
