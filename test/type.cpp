/* Testing type logic */
#include <systemc.h>
using namespace std;

int
sc_main(int, char **)
{
	bool bf =  false, bt = true;
	sc_logic f(0), t(1), z('z'), x('x');
	sc_logic i(3);
	sc_lv<8> lvb = "01ZX01ZX";
	sc_lv<8> lvc = 42;
	sc_lv<8> lvd = false;
	sc_bv<8> bvb = 9;
	sc_bv<8> bvc = true;
	sc_lv<4> lve = bvb(6, 3);
	sc_bv<4> bvd = lvb(6, 3);
	sc_int<42> a = lvb;
	sc_uint<42> b = 123456789;
	sc_lv<42> lvf = a;

	cout << f << t << z << x << i << endl;
	cout << ~x << (f ^ t) << (z & x) << endl;
	cout << (f | false) << (x | false) << (z | false) << endl;
	cout << (bf | t) << (bt ^ z) << (bf & i) << endl;

	cout << lvb << endl << lvc << endl << lvd << endl;
	cout << bvb << endl << bvc << endl;
	cout << (lvb ^ lvc) << endl << (lvc & lvd) << endl;
	cout << (lvb ^ bvb) << endl << (lvc | bvc) << endl;
	cout << lve << endl << bvd << endl;

	cout << a << endl << b << endl << lvf << endl;
	cout << (a + b) << endl << (a || b) << endl;

	return 0;
}
