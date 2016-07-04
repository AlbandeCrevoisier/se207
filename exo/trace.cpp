/* Print trace with gtk wave */
#include <systemc.h>

int
sc_main (int argc, char *argv[])
{
	int idx;
	int n = atoi(argv[1]);
	if (n > 255 || argc != 2) {
		cout << "Format: exe arg where arg < 255." << endl;
		return 0;
	}

	// Un pointeur sur l'objet qui permet de gérer les traces
	sc_trace_file *trace_f;

	/* Cette fonction crée l'objet
	 * L'argument est le nom du fichier qui sera créé.
	 * L'extension .vcd est ajoutée automatiquement
	 */
	trace_f = sc_create_vcd_trace_file ("my_simu_trace");
	// On peut aussi préciser l'unité de temps dans le fichier vcd
	trace_f->set_time_unit(1,SC_PS);

	
	/* Ajoute la variable t aux éléments à tracer
	 * Les arguments de la fonction sont:
	 *  - le pointeur vers le fichier de trace
	 *  - la variable/objet à tracer
	 *  - le nom dans dans le fichier généré
	 */
	bool t;
	sc_trace(trace_f, t, "t");

	// La simulation
	sc_trace(trace_f, idx, "idx");
	for (int i = 0; i < 4; i++) {
		t = !t;
		idx = 0;
		for (int j = 0; j < n; j++) {
			sc_start(10000/n, SC_PS);
			idx++;
		}
	}

	/* Ferme le fichier de trace
	 * ne peut êter fait qu'à la fin de la simulation
	 */
	sc_close_vcd_trace_file(trace_f);

	return 0;
}
