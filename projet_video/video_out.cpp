#include "video_out.h"

#define W 720
#define H 576

void
VIDEO_OUT::gen_pic()
{
	if (reset_n == false) {
		int i, j;
		for (i = 0; i < H; i++)
			for (j = 0; j < W; j++)
				image.pixel[i * image.width + j];
		read_stream();
	}
}

void
VIDEO_OUT::read_stream()
{
}
