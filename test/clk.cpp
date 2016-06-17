/* Print the trace of the clock signals. */
#include <systemc.h>

int
sc_main(int, char **)
{
	bool first_edge = true;
	double D = 0.4;
	sc_time T(25,SC_NS);
	sc_time ST(200,SC_NS);
	sc_clock ck1("ck1",10,SC_NS);
	sc_clock ck2("ck2",T);
	/* Periode 10ns, duty cycle 25%, starts @150ns by negedge */
	sc_clock ck3("ck3",10,SC_NS,0.25,150,SC_NS,false);
	sc_clock ck4("ck4",T,D,ST,first_edge);
	sc_trace_file *t_f;

	t_f = sc_create_vcd_trace_file("clk_trace");
	t_f->set_time_unit(1, SC_NS);
	sc_trace(t_f, ck1, "ck1");
	sc_trace(t_f, ck2, "ck2");
	sc_trace(t_f, ck3, "ck3");
	sc_trace(t_f, ck4, "ck4");

	sc_start(500, SC_NS);

	sc_close_vcd_trace_file(t_f);

	return 0;
}
