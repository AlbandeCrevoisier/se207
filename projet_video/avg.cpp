#include "avg.h"

void
FILTER_AVG::avg()
{
	int i, j;
	int w = buf.width;
	int h = buf.height;

	if (reset_n == false) {
		vref_out = false;
		href_out = false;
		pixel_out = 0;
		i = 0;
		j = 0;
		cout << name() << " reset." << endl;
	}

	while (1) {
		wait(vref_in.posedge_event());
		cout << name() << " recieving pic." << endl;
		for (i = 0; i < h + 2; i++) {
			if (i < h)
				wait(href_in.posedge_event());
			for (j = 0; j < w; j++) {
				wait();
				buf.pixel[(i * w) % 3 + j] = pixel_in;

				if (i > 1) {
					int a = i - 2;
					int u, d;
					int l, r;
					int tmp = 0;

					vref_out = (a < 3);
					href_out = true;

					u = (a ? 1 : (a - 1));
					d = ((a == h - 1) ? h - 2 : a + 1);
					l = (j ? 1 : (j - 1));
					r = ((j == w - 1) ? w - 2 : j + 1);

					tmp += buf.pixel[((3 + u) % 3) * w + l];
					tmp += buf.pixel[((3 + u) % 3) * w + j];
					tmp += buf.pixel[((3 + u) % 3) * w + r];
					tmp += buf.pixel[(a % 3) * w + l];
					tmp += buf.pixel[(a % 3) * w + j];
					tmp += buf.pixel[(a % 3) * w + r];
					tmp += buf.pixel[(d % 3) * w + l];
					tmp += buf.pixel[(d % 3) * w + j];
					tmp += buf.pixel[(d % 3) * w + r];

					tmp /= 9;

					pixel_out = tmp;
				}
			}
			href_out = false;
		}
	}
}
