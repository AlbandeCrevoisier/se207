/* to put i in o: create a method with a sensibility on i, and in it o = i */




/* signal and modules */
#include <systemc.h>

SC_MODULE(foo) {
	sc_in <bool> i;
	sc_out<bool> o;
	SC_CTOR(foo):i("i"),o("o")
	{
		
	}
};

SC_MODULE(bar) {
	sc_in <bool> i;
	sc_out<bool> o;
	SC_CTOR(bar):i("i"),o("o")
	{
		
	}
};

SC_MODULE(foobar) {
	// entrée/sortie
	sc_in <bool> i;
	sc_out<bool> o;
	// interne
	sc_signal<bool> s;
	// sous modules
	foo foo_i;
	bar bar_i;

	SC_CTOR(foobar)
		:i("i"),o("o"),s("s"),
		foo_i("foo"), bar_i("bar")
	{
		// connexions aux I/O
		foo_i.i(i);
		bar_i.o(o);
		// connexion interne
		foo_i.o(s);
		bar_i.i(s);
	}
};

int
sc_main(int, char **)
{
	sc_signal<bool> o("o");
	sc_clock clk("clk", 10, SC_NS);
	sc_trace_file *t_f;
	foobar uut("foobar");

	t_f = sc_create_vcd_trace_file("mod_t");
	t_f->set_time_unit(1, SC_NS);
	sc_trace(t_f, clk, "clk");
	sc_trace(t_f, o, "o");
	sc_trace(t_f, uut.s, "s");

	uut.i(clk);
	uut.o(o);

	sc_start(100, SC_NS);

	sc_close_vcd_trace_file(t_f);

	return 0;
}
