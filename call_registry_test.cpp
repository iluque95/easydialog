#include <iostream>
#include "incl/call_registry.hpp"

#include <bits/stdc++.h>
#include <fstream>

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

nat random_nat()
{
    return (rand() % 999999999) + 100000000;
}

void log(const string &str)
{
    ofstream outfile("dump.log", ofstream::app);
    outfile << str << endl;
    outfile.close();
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
        cout << "\033[1;31mERROR: \033[0m" << e.mensaje() << endl;
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

    for (nat i = 1; i <= 24; ++i)
    {
        char c = 64 + i;
        std::string s(1, c);
        cr.registra_trucada(i);

        try
        {
            cr.assigna_nom(i, s);
        }
        catch (error e)
        {
            cout << "\033[1;31mERROR: \033[0m" << e.mensaje() << ". Inserting -> " << s << endl;
        }
    }

    cout << "El nom del telefon 661635963 és: " << cr.nom(661635963) << endl;

    cout << "Registring random calls..." << endl;

    srand(time(0)); // Initialize random number generator.

    for (nat i = 0; i < 50; ++i)
    {
        cr.registra_trucada(random_nat());
    }

    remove("dump.log");

    vector<nat> nums;

    for (nat i = 0; i < 1000; ++i)
    {
        string name;
        nat offset = (rand() % 10) + 1;
        name.reserve(i % 5 + 25 + offset);
        random_str(name, i % 5 + 25 + offset);

        nat num = random_nat();

        cr.registra_trucada(num);

        nums.push_back(num);

        log(name);

        try
        {
            cr.assigna_nom(num, name);
        }
        catch (error e)
        {
            cout << "\033[1;31mERROR: \033[0m" << e.mensaje() << ". Inserting -> " << name << endl;
        }
    }

    call_registry aux(cr);

    if (not aux.es_buit())
    {
        cout << "\033[1;31mERROR: \033[0m"
             << "El call registry está buit" << endl;
    }

    dump(cr);

    for (nat i = 0; i < 10; ++i) //nums.size() / 2
    {
        try
        {
            cr.elimina(nums[i]);
        }
        catch (error e)
        {
            cout << "No existeix el número " << nums[i] << endl;
        }
    }

    cout << "Testing a little call_registry deleting stuff..." << endl;

    call_registry cr_little;

    for (nat i = 1; i <= 3; ++i)
    {
        cr_little.registra_trucada(i);
    }

    for (nat i = 1; i <= 3; ++i)
    {
        string str;
        str.reserve(1);

        str.push_back('a' + i);

        cr_little.assigna_nom(i, str);
    }

    dump(cr_little);

    cout << "Deleting..." << endl;

    cr_little.elimina(3);

    dump(cr_little);

    cr_little.elimina(2);

    if (not cr_little.es_buit())
        dump(cr_little);

    cout << "End of testing call_registry..." << endl;
}