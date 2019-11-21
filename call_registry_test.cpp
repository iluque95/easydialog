#include <iostream>
#include <iostream>
#include "incl/call_registry.hpp"

using namespace std;

int main()
{
    cout << "Testing call_registry..." << endl;

    call_registry cr;
    if (cr.es_buit()) {
        cout << "El call_registry está buit..." << endl;
    } else {
        cout << "Houston, we have a problem!" << endl;
    }

    cout << "Registring call..." << endl;

    cr.registra_trucada(661635963);
    cout << "El número de trucades actual és: " << cr.num_trucades(661635963) << endl;

    cout << "Assigning name to last call..." << endl;
    cr.assigna_nom(661635963, "Itiel");

    cout << "El nom del telefon 661635963 és: " << cr.nom(661635963) << endl;

    cout << "Registring random calls..." << endl;

    nat number = 0;

    for (nat i = 0; i < 20; ++i)
    {
        util::Random R2;

        number = R2(314159);//(100000000,999999999);

        cr.registra_trucada(number);
        cout << "Entrades: " << cr.num_entrades() << endl;
        cout << "Conté " << number << " ? " << (cr.conte(number) ? "Sí" : "No") << endl;
    }

    cr.statistic();

    cr.assigna_nom(number, "Marcos");

    cout << "Number " << number << " with name " << cr.nom(number) << endl;

    cout << "End of testing call_registry..." << endl;
}