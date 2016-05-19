/* Testing type logic */
#include <systemc.h>
#include <iostream>
using namespace std;

int
sc_main(int argc, char *argv[])
{
    sc_logic f(0), t(1), z('z'), x('x');
    sc_logic i(3);
    cout << f << t << z << x << i << endl;
    cout << ~x << (f ^ t) << (z & x) << endl;
    cout << (f | true) << (true | x) << endl;

    return 0;
}

