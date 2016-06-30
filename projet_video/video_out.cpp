#include "video_out.h"

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
		for (i = 0; i < image.height; i++) {
			wait(href.posedge_event());
			for (j = 0; j < image.width; j++) {
				wait();
				image.pixel[i * image.width + j] = pixel_in;
			}
		}
		f_name = (base_name + std::to_string(n_image++)).c_str();
		cout << name() << ": writing " << f_name << endl;
		image_write(&image, f_name);
	}
}
