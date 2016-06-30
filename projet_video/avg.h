/* Filter: average on a 3 * 3 square. */
#ifndef AVG_H
#define AVG_H

#include <systemc.h>
#include "image.h"

SC_MODULE(FILTER_AVG) {
	sc_in<bool> clk;
	sc_in<bool> reset_n;

	sc_in<bool> vref_in;
	sc_in<bool> href_in;
	sc_in<unsigned char> pixel_in;

	sc_out<bool> vref_out;
	sc_out<bool> href_out;
	sc_out<unsigned char> pixel_out;

	SC_CTOR(FILTER_AVG) {
		cout << "Begin instanciation of " << name() << "." << endl;

		SC_THREAD(avg);
		sensitive << clk.pos();
		async_reset_signal_is(reset_n, false);
		dont_initialize();

		vref = false;
		href = false;

		width = 720;
		height = 576;
		buf = (unsigned char *)
			malloc(width * 3 * sizeof(unsigned char));
	}

	private:
	void avg();

	unsigned char *buf;
	int width;
};

#endif /* AVG_H */
