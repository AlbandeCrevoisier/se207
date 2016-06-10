/* Print trace with gtk wave */
#include <systemc.h>

int
sc_main (int argc, char *argv[])
{
	uint8_t n = atoi(argv[1]);
	uint8_t idx = 0;

	// Un pointeur sur l'objet qui permet de gérer les traces
	sc_trace_file *trace_f;

	/* Cette fonction crée l'objet
	 * L'argument est le nom du fichier qui sera créé.
	 * L'extension .vcd est ajoutée automatiquement
	 */
	trace_f = sc_create_vcd_trace_file ("my_simu_trace");
	// On peut aussi préciser l'unité de temps dans le fichier vcd
	trace_f->set_time_unit(1,SC_NS);

	
	/* Ajoute la variable t aux éléments à tracer
	 * Les arguments de la fonction sont:
	 *  - le pointeur vers le fichier de trace
	 *  - la variable/objet à tracer
	 *  - le nom dans dans le fichier généré
	 */
	bool t;
	sc_trace(trace_f, t, "t");

	int i;
	sc_trace(trace_f, i, "i");
	int N = atoi(argv[1]);
	for (i = 0; i < N; i++) {
		sc_start(10, SC_NS);
	}

	// La simulation
	sc_start(10,SC_NS);
	t = !t; 
	sc_start(10,SC_NS);
	t = !t; 
	sc_start(10,SC_NS);
	t = !t; 
	sc_start(10,SC_NS);

	/* Ferme le fichier de trace
	 * ne peut êter fait qu'à la fin de la simulation
	 */
	sc_close_vcd_trace_file(trace_f);

	return 0;
}
