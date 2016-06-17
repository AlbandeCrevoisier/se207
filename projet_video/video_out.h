#ifndef VIDEO_OUT_H
#define VIDEO_OUT_H

#include <systemc.h>
#include "image.h"

SC_MODULE(VIDEO_OUT) {
	sc_in<bool> clk;
	sc_in<bool> reset_n;
	sc_in<unsigned char> pixel_in;
	sc_in<bool> href;
	sc_in<bool> vref;

	

#endif // VIDEO_OUT_H