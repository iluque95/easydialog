#include <iostream>
#include <iostream>
#include "incl/call_registry.hpp"

#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()

#include <bits/stdc++.h> 



using namespace std;

void random_str(string &s, const nat len)
{
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (nat i = 0; i < len; ++i)
    {
        s.push_back(alphanum[rand() % (sizeof(alphanum) - 1)]);
    }

    s[len] = 0;
}

nat random_nat(nat &i)
{
    srand(time(0));  // Initialize random number generator.

    return rand();//(rand() % 999999999) + 100000000;;
}

int randomNoGenerator(int limit) 
{ 
    // uniformly-distributed integer random number 
    // generator that produces non-deterministic 
    // random numbers. 
    random_device rd; 
  
    // A Mersenne Twister pseudo-random generator 
    // of 32-bit numbers with a state size of 
    // 19937 bits. 
    mt19937 gen(rd()); 
  
    // Uniform distribution 
    uniform_int_distribution<> dis(1, limit); 
    return dis(gen); 
} 

void dump(call_registry &cr)
{
    cout << "#####################################################################################" << endl;
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

        cout << "-----------" << endl
             << endl;

        cout << "String hash table V[0]: " << endl
             << endl;
        cout << "\t[SHT] Frequency: " << V[0].frequencia() << ", Number: " << V[0].numero() << endl;
        cout << "\t[NHT] Frequency: " << cr.num_trucades(V[0].numero()) << ", Number: " << V[0].numero() << endl
             << endl;

        cout << "Registring once more time the last shown call..." << endl
             << endl;

        cr.registra_trucada(V[0].numero());

        cout << "\t[SHT] Frequency: " << V[0].frequencia() << ", Number: " << V[0].numero() << endl;
        cout << "\t[NHT] Frequency: " << cr.num_trucades(V[0].numero()) << ", Number: " << V[0].numero() << endl
             << endl;

        /*
        if (V[5].frequencia() != cr.num_trucades(V[5].numero()))
        {
            cout << "\033[1;31mERROR: SHT != NHT  ! ! !\033[0m" << endl
                 << endl;
        }
        */
    }
    catch (error e)
    {
        cout << "Error: " << e.mensaje() << endl;
    }
    cout << "#####################################################################################" << endl
         << endl;
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

    cr.registra_trucada(1);
    cr.assigna_nom(1, "A");

    cr.registra_trucada(2);
    cr.assigna_nom(2, "B");

    cr.registra_trucada(3);
    cr.assigna_nom(3, "C");

    cr.registra_trucada(4);
    cr.assigna_nom(4, "D");

    cr.registra_trucada(5);
    cr.assigna_nom(5, "E");

    cr.registra_trucada(6);
    cr.assigna_nom(6, "F");

    cr.registra_trucada(7);
    cr.assigna_nom(7, "G");

    cr.registra_trucada(8);
    cr.assigna_nom(8, "H");

    cr.registra_trucada(9);
    cr.assigna_nom(9, "I");

    cr.registra_trucada(10);
    cr.assigna_nom(10, "J");

    cr.registra_trucada(11);
    cr.assigna_nom(11, "K");

    cr.registra_trucada(12);
    cr.assigna_nom(12, "L");

    cr.registra_trucada(13);
    cr.assigna_nom(13, "M");

    cr.registra_trucada(14);
    cr.assigna_nom(14, "N");

    cr.registra_trucada(15);
    cr.assigna_nom(15, "O");



    cout << "El nom del telefon 661635963 és: " << cr.nom(661635963) << endl;

    cout << "Registring random calls..." << endl;

    for (nat i = 0; i < 20; ++i)
    {
        cr.registra_trucada(randomNoGenerator(100000000));
    }
/*
    for (nat i = 0; i < 30; ++i)
    {
        string name;
        name.reserve(5 + i);
        random_str(name, 5 + i);
        cout << "El nom en la posició " << i << " és igual a: " << name << endl;

        nat num = randomNoGenerator(100000000);

        cr.registra_trucada(num);
        cr.assigna_nom(num, name);
    }
*/
    dump(cr);

    cout << "End of testing call_registry..." << endl;
}