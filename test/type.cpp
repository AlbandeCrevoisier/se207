/* Testing type logic */
#include <systemc.h>
using namespace std;

int
sc_main(int argc, char *argv[])
{
	bool bf =  false, bt = true;
	sc_logic f(0), t(1), z('z'), x('x');
	sc_logic i(3);

	cout << f << t << z << x << i << endl;
	cout << ~x << (f ^ t) << (z & x) << endl;
	cout << (f | false) << (x | false) << (z | false) << endl;

	cout << (bf | t) << (bt ^ z) << (bf & i) << endl;

	return 0;
}
