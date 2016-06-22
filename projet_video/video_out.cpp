#include <ofstream>
#include "video_out.h"

#define W 720
#define H 576

void
VIDEO_OUT::read_stream()
{
	int i, j;
	int n_image = 0;
	char *f_name = base_name.std::c_str();

	if (reset_n == false) {
		i = 0;
		j = 0;
	}

	while (1) {
		for (i = 0; i < H; i++) {
			j = 0;
			while (href == 1) {
				wait();
				image.pixel[i * image.width + j++] = pixel_in;
			}
		}
		gen_pic(f_name + std::to_string(n_image++));
	}
}

void
VIDEO_OUT::gen_pic(const char *f_name)
{
	ofstream f;
	fopen(/*name*/);
	image_write(&image, f_name);
}
