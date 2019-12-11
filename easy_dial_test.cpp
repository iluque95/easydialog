#include <iostream>
#include <vector>
#include <string>
#include "incl/easy_dial.hpp"
#include "incl/phone.hpp"
#include "incl/call_registry.hpp"

using namespace std;

void search(const easy_dial &ed, const string &str)
{

    vector<string> v;

    cout << "Searching phone numbers starting with prefix " << str << "..." << endl;

    ed.comencen(str, v);

    cout << "Size of vector: " << v.size() << endl;

    cout << "Values of vector:" << endl;

    cout << "{";
    for (nat i = 0; i < v.size(); ++i)
        cout << " \033[0;33m[" << i << "]\033[0m => \"\033[0;34m" << v[i] << "\033[0m\"";

    cout << " }" << endl;
}

int main()
{
    cout << "Testing easy_dial..." << endl;

    call_registry cr;

    cr.registra_trucada(44555);

    cr.assigna_nom(44555, "Itiel");

    cr.assigna_nom(666, "Devil");

    cr.assigna_nom(3434, "Invented name");

    cr.assigna_nom(2223, "Doraemon");

    cr.assigna_nom(2228, "Soraya");

    easy_dial ed(cr);

    cout << "Inici: " << ed.inici() << endl;

    cout << "Seguent D (Pref: D): " << ed.seguent('D') << endl;

    cout << "Seguent E (Pref: De): " << ed.seguent('e') << endl;

    cout << "Inici: " << ed.inici() << endl;

    cout << "Seguent S (Pref: S): " << ed.seguent('S') << endl;

    search(ed, "I");

    search(ed, "D");

    search(ed, "");

    call_registry cr2;

    cr2.assigna_nom(44555, "JOSEP");

    cr2.registra_trucada(44555);
    cr2.registra_trucada(44555);
    cr2.registra_trucada(44555);
    cr2.registra_trucada(44555);
    cr2.registra_trucada(44555);
    cr2.registra_trucada(44555);
    cr2.registra_trucada(44555);
    cr2.registra_trucada(44555);
    cr2.registra_trucada(44555);
    cr2.registra_trucada(44555);
    cr2.registra_trucada(44555);
    cr2.registra_trucada(44555);
    cr2.registra_trucada(44555);
    cr2.registra_trucada(44555);
    cr2.registra_trucada(44555);
    cr2.registra_trucada(44555);
    cr2.registra_trucada(44555);
    cr2.registra_trucada(44555);
    cr2.registra_trucada(44555);

    cr2.assigna_nom(34534534, "MIQUEL");

    cr2.registra_trucada(34534534);
    cr2.registra_trucada(34534534);
    cr2.registra_trucada(34534534);
    cr2.registra_trucada(34534534);
    cr2.registra_trucada(34534534);
    cr2.registra_trucada(34534534);
    cr2.registra_trucada(34534534);
    cr2.registra_trucada(34534534);

    cr2.assigna_nom(435345, "ELEGIR");

    cr2.registra_trucada(435345);
    cr2.registra_trucada(435345);
    cr2.registra_trucada(435345);
    cr2.registra_trucada(435345);
    cr2.registra_trucada(435345);
    cr2.registra_trucada(435345);

    cr2.assigna_nom(687678, "ITIEL");

    cr2.registra_trucada(687678);
    cr2.registra_trucada(687678);
    cr2.registra_trucada(687678);
    cr2.registra_trucada(687678);
    cr2.registra_trucada(687678);
    cr2.registra_trucada(687678);
    cr2.registra_trucada(687678);

    easy_dial ed2(cr2);

    search(ed2, "");

    cout << "End of testing easy_dial..." << endl;
}