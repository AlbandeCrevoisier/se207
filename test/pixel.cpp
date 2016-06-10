/* Pixel struct */
#include <systemc.h>
using namespace std;

// un type utilisateur
struct pt_t {
	int i;
	int j;
	// un constructeur particulier avec des valeurs par défaut
	pt_t( int _i=0, int _j=1): i(_i), j(_j) { }

	bool operator == (const pt_t &other) {
		return (i == other.i) && (j == other.j);
	}
	/* Comment ce type est imprimé
	 * l'opérateur << est un opérateur de la classe std::ostream
	 */
	friend ostream& operator << ( ostream& o, const pt_t& P ) {
		o << "{" << P.i << "," << P.j << "}" ;
		return o;
	}
};

struct p_t {
	sc_uint<5> r;
	sc_uint<6> g;
	sc_uint<5> b;

	p_t(int _r = 0, int _g = 0, int _b = 0): r(_r), g(_g), b(_b) { }

	bool operator == (const p_t &other) {
		return (r == other.r) && (g == other.g) && (b == other.b);
	}

	friend ostream& operator << (ostream& o, const p_t& p) {
		o << "Pixel {" << p.r << ", " << p.g << ", " << p.b << "}";
		return o;
	}
};
	
// surcharge de la fonction sc_trace pour le type utilisateur
void
sc_trace( sc_trace_file* _f, const pt_t& _foo, const std::string& _s )
{
	sc_trace( _f, _foo.i, _s + "_i" );
	sc_trace( _f, _foo.j, _s + "_j" );
}

/* sc_trace overload for p_t */
void
sc_trace(sc_trace_file *_f, const p_t& _p, const string& _s)
{
	sc_trace(_f, _p.r, _s + "_r");
	sc_trace(_f, _p.g, _s + "_g");
	sc_trace(_f, _p.b, _s + "_b");
}

// Le test
int
sc_main (int, char **)
{
	sc_trace_file *f_t;
	f_t = sc_create_vcd_trace_file ("pixel_trace");
	f_t->set_time_unit(1, SC_NS);

	sc_signal<pt_t> P;
	cout << "--> @ " << sc_time_stamp() << " P = " << P << endl;

	// affectation au signal
	P = pt_t(33,22);
	cout << "--> @ " << sc_time_stamp() << " P = " << P << endl;

	cout << "==========" << endl;

	sc_signal<p_t> p;
	sc_trace(f_t, p, "pixel");
	p_t pixel_tmp = p_t(9, 17, 42);
	cout << "--> @" << sc_time_stamp() << " p = " << p << endl;
	p = pixel_tmp;
	cout << "--> @" << sc_time_stamp() << " p = " << p << endl;
	sc_start(10, SC_NS);
	cout << "--> @" << sc_time_stamp() << " p = " << p << endl;
	pixel_tmp.r++;
	p = pixel_tmp;
	sc_start(10, SC_NS);
	cout << "--> @" << sc_time_stamp() << " p = " << p << endl;

	sc_start(10, SC_NS);

	sc_close_vcd_trace_file(f_t);

	return 0;
}
