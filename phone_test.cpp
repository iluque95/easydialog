#include <iostream>
#include <iostream>
#include "incl/phone.hpp"

using namespace std;

int main()
{
    cout << "Testing phone..." << endl;

    phone p(75745455, "Messi", 0);

    cout << "Telèfon de " << p.nom() << " es " << p.numero() << endl;

    cout << "Es 1 > " << p.frequencia() << " ? " << ((1 > p.frequencia()) ? "Si" : "NO!") << endl;

    ++p;

    cout << "Preincremento." << endl;

    cout << "Es 1 > " << p.frequencia() << " ? " << ((1 > p.frequencia()) ? "Si" : "NO!") << endl;

    p++;

    cout << "Postincremento." << endl;

    cout << "Es 1 > " << p.frequencia() << " ? " << ((1 > p.frequencia()) ? "Si" : "NO!") << endl;

    cout << "Es 2 == " << p.frequencia() << " ? " << ((2 == p.frequencia()) ? "Si" : "NO!") << endl;

    cout << "Es 10 != " << p.frequencia() << " ? " << ((10 != p.frequencia()) ? "Si" : "NO!") << endl;

    try
    {
        phone p2(11111, "<", 0);
        cout << "Telèfon de " << p2.nom() << " es " << p2.numero() << endl;
    }
    catch (error e)
    {
        cerr << "Error en la classe " << e.modulo() << " amb codi " <<  e.codigo() << " => " << e.mensaje() << endl;
    }

    cout << "End of testing phone..." << endl;
}