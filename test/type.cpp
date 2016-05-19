/* Testing type logic */
#include <systemc.h>
#include <iostream>

int
sc_main(int argc, char *argv[])
{
    sc_logic u(1);
    cout << u << endl;

    u = 0;
    cout << u << endl;
    
    u = 'z';
    cout << u << endl;

    u = 'x';
    cout << u << endl;

    return 0;
}

