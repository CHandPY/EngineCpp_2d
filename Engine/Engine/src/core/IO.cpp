#include "IO.h"

namespace engine {
	namespace core {

		std::string* IO::load(const char *filepath, int *length) {
			FILE *fp = std::fopen(filepath, "r");

			if (!fp) {
				std::cerr << "Failled to oppen file: " << filepath << std::endl;
				return 0;
			}

			std::vector<std::string> *lines = new std::vector<std::string>();

			char line[CHAR_AMT];
			while (fgets(line, 1023, fp)) {
				lines->push_back(std::string(line));
			}

			fclose(fp);

			*length = lines->size();

			return &(*lines)[0];
		}

		unsigned char * IO::loadPNG(unsigned& width, unsigned& height, char * filepath) {
			std::vector<unsigned char> image;
			unsigned error = lodepng::decode(image, width, height, filepath);

			if (error) {
				std::cout << lodepng_error_text(error) << std::endl;
				return nullptr;
			}

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
	}
}
