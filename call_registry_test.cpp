#include <iostream>
#include <iostream>
#include "incl/call_registry.hpp"

using namespace std;

void random_str(string &s, const nat len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (nat i = 0; i < len; ++i) {
        s.push_back(alphanum[rand() % (sizeof(alphanum) - 1)]);
    }

    s[len] = 0;
}

nat random_nat(nat &i)
{
    util::Random R2;

    return R2(314159 + i * i);
}

int main()
{
    cout << "Testing call_registry..." << endl;

    call_registry cr;
    if (cr.es_buit())
    {
        cout << "El call_registry está buit..." << endl;
    }
    else
    {
        cout << "Houston, we have a problem!" << endl;
    }

    cout << "Registring call..." << endl;

    cr.registra_trucada(661635963);
    cout << "El número de trucades actual és: " << cr.num_trucades(661635963) << endl;

    cout << "Assigning name to last call..." << endl;
    cr.assigna_nom(661635963, "Itiel");

    cout << "El nom del telefon 661635963 és: " << cr.nom(661635963) << endl;

    cout << "Registring random calls..." << endl;


    for (nat i = 0; i < 20; ++i)
    {
        cr.registra_trucada(random_nat(i));
    }

    for (nat i = 0; i < 5; ++i)
    {
        string name;
        name.reserve(5+i);
        random_str(name, 5+i);

        nat num = random_nat(i);

        cr.registra_trucada(num);
        cr.assigna_nom(num,name);
    }

    vector<phone> V;
    try
    {
        cout << endl;
        cout << "Dump method" << endl;
        cout << "-----------" << endl;

        cr.dump(V);
        cout << "La mida del vector és: " << V.size() << endl;

        cout << "{";
        for (nat i = 0; i < V.size(); ++i)
            cout << " \033[0;33m[" << i << "]\033[0m => \"\033[0;34m" << V[i].nom() << "\033[0m\"";

        cout << " }" << endl;

        cout << "-----------" << endl << endl;

        cout << "String hash table V[5]: " << endl << endl;
        cout << "\t[SHT] Frequency: " << V[5].frequencia() << ", Number: " << V[5].numero() << endl;
        cout << "\t[NHT] Frequency: " << cr.num_trucades(V[5].numero()) << ", Number: " << V[5].numero() << endl << endl;

        cout << "Registring once more time the last shown call..." << endl << endl;

        cr.registra_trucada(V[5].numero());

        cout << "\t[SHT] Frequency: " << V[5].frequencia() << ", Number: " << V[5].numero() << endl;
        cout << "\t[NHT] Frequency: " << cr.num_trucades(V[5].numero()) << ", Number: " << V[5].numero() << endl << endl;

        if (V[5].frequencia() != cr.num_trucades(V[5].numero()))
             cout << "\033[1;31mERROR: SHT != NHT  ! ! !\033[0m" << endl << endl;
        
    }
    catch (error e)
    {
        cout << "Error: " << e.mensaje() << endl;
    }

    cout << "End of testing call_registry..." << endl;
}