#include "video_out.h"

#define W 720
#define H 576

void
VIDEO_OUT::read_stream()
{
	int i, j;
	int n_image = 0;

	if (reset_n == false) {
		i = 0;
		j = 0;
		n_image = 0;
		cout << name() << " reset." << endl;
	}

	while (1) {
		const char *f_name;
		wait(vref.posedge_event());
		cout << "Reading image..." << endl;
		for (i = 0; i < H; i++) {
			j = 0;
			while (href == 1) {
				wait();
				image.pixel[i * image.width + j++] = pixel_in;
			}
		}
		f_name = (base_name + std::to_string(n_image++)).c_str();
		image_write(&image, f_name);
	}
}
