#include "avg.h"

void
FILTER_AVGT::avg()
{
	int i, j;

	if (reset_n == false) {
		vref_out = false;
		href_out = true;
		pixel_out = 0;
		i = 0;
		j = 0;
		cout << name() << " reset." << endl;
	}

	while (1) {
		wait(vref_in.posedge_event());
		for (i = 0; i < height; i++) {
			wait(href_in.posedge_event());
			for (j = 0; j < width; j++) {
				wait();
				buf[(i * width) % 3 + j] = pixel;
			}

			vref = (i < 3);

			if (2 < i) {
				int up, down;
				int left, right;
				int tmp = 0;

				href_out = true;

				up = (i ? 1 : (i - 1));
				down = ((i == height - 1) ? height - 2 : i + 1);
				left = (j ? 1 : (j - 1));
				right = ((j == width - 1) ? width - 2 : j + 1);

				tmp += buf[((3 + up) % 3) * width + left];
				tmp += buf[((3 + up) % 3) * width + j];
				tmp += buf[((3 + up) % 3) * width + right];
				tmp += buf[(i % 3) * width + left];
				tmp += buf[(i % 3) * width + j];
				tmp += buf[(i % 3) * width + right];
				tmp += buf[(down % 3) * width + left];
				tmp += buf[(down % 3) * width + j];
				tmp += buf[(down % 3) * width + right];
				
				tmp /= 9;

				pixel_out = tmp;
			}
			href_out = false;
		}
	}
}
