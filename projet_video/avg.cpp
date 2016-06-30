#include "avg.h"

void
FILTER_AVGT::avg()
{
	int i_in, j_in;
	int i_out, j_out;

	if (reset_n == false) {
		vref_out = false;
		href_out = true;
		pixel_out = 0;
		i_out = 0;
		j_out = 0;
		i_in = 0;
		j_in = 0;
		cout << name() << " reset." << endl;
	}

	while (1) {
		wait(vref.posedge_event());
		for (i_in = 0; i_in < height; i_in++) {
			wait(href.posedge_event());
			for (j_in = 0; j_in < width; j_in++) {
				wait();
				buf[i_in * width + j_in] = pixel_in;
			}
			if (2 < i_in && i_in < height - 1) {
				
			}
		}
	}
}
