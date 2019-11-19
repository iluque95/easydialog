#include <iostream>
#include <iostream>
#include "incl/call_registry.hpp"

using namespace std;

int main()
{
    cout << "Testing call_registry..." << endl;

    call_registry cr;

    cout << "Registring call..." << endl;
    cr.registra_trucada(661635963);

    cout << "Assigning name to last call..." << endl;
    cr.assigna_nom(661635963, "Itiel");

    cout << "Registring random calls..." << endl;

   

    for (nat i = 0; i < 20; ++i)
    {
        util::Random R;
        cr.registra_trucada(R(100000000,999999999));
    }

    cout << "End of testing call_registry..." << endl;
}