#include "call_registry.hpp"
#include <bits/stdc++.h>

// θ(n)
template <typename Clau>
call_registry::diccionari<Clau>::diccionari() throw(error) : m_mida(mida_inicial),
                                                             m_quants(0),
                                                             colisions(0),
                                                             redispersions(0),
                                                             shrinks(0),
                                                             total(0)
{
    //PRE: TRUE
    //POST: Crea un diccionar buit
    m_taula = new node_hash *[m_mida];

    for (nat i = 0; i < m_mida; ++i)
    {
        m_taula[i] = NULL;
    }
}

// θ(n)
template <typename Clau>
call_registry::diccionari<Clau>::diccionari(const diccionari &d) throw(error) : m_mida(d.m_mida),
                                                                                m_quants(d.m_quants),
                                                                                colisions(d.colisions),
                                                                                redispersions(d.redispersions),
                                                                                shrinks(d.shrinks),
                                                                                total(d.total)
{
    //PRE: TRUE
    //POST: p.i. és una copia idéntica de d
    m_taula = new node_hash *[m_mida];

    for (nat i = 0; i < m_mida; ++i)
    {
        m_taula[i] = NULL;

        if (d.m_taula[i] != NULL)
        {
            m_taula[i] = new node_hash;
            m_taula[i]->m_clau = d.m_taula[i]->m_clau;
            m_taula[i]->m_valor = new phone(*d.m_taula[i]->m_valor);
            m_taula[i]->m_seg = NULL;

            node_hash *n = d.m_taula[i]->m_seg;
            node_hash *act = m_taula[i];

            while (n != NULL)
            {
                node_hash *aux = new node_hash;

                aux->m_clau = n->m_clau;
                aux->m_valor = new phone(*n->m_valor);
                aux->m_seg = NULL;

                act->m_seg = aux;

                n = n->m_seg;
                act = act->m_seg;
            }
        }
    }
}

// θ(n)
template <typename Clau>
call_registry::diccionari<Clau> &call_registry::diccionari<Clau>::operator=(const diccionari &d) throw(error)
{
    //PRE: TRUE
    //POST: Al p.i. se li assignen tots els valors de d
    if (this != &d)
    {
        diccionari<Clau> dicc(d);

        node_hash **tmp = m_taula;

        m_taula = dicc.m_taula;
        dicc.m_taula = tmp;

        nat val = m_mida;

        m_mida = dicc.m_mida;
        dicc.m_mida = val;

        val = m_quants;

        m_quants = dicc.m_quants;
        dicc.m_quants = val;

        val = total;

        total = dicc.total;
        dicc.total = val;
    }

    return *this;
}

// θ(n)
template <typename Clau>
call_registry::diccionari<Clau>::~diccionari() throw()
{
    //PRE: TRUE
    //POST: S'elimina de memoría el diccionari del p.i.
    for (nat i = 0; i < m_mida; ++i)
    {
        node_hash *prev = NULL;
        node_hash *act = NULL;

        if (m_taula[i] != NULL)
        {
            act = m_taula[i]->m_seg;

            delete m_taula[i]->m_valor;
            delete m_taula[i];
        }

        while (act != NULL)
        {
            prev = act;
            act = act->m_seg;

            delete prev->m_valor;
            delete prev;
        }
    }

    delete[] m_taula;
}

// θ(1)
template <typename Clau>
void call_registry::diccionari<Clau>::insereix(const Clau &c, phone *&p)
{
    //PRE: TRUE
    //POST: Inserta al diccionari un node amb la Clau C i el phone p
    nat i = hash(c);

    if (m_taula[i] == NULL)
        ++m_quants;
    else
        ++colisions;

    ++total;

    node_hash *n = new node_hash;

    n->m_clau = c;
    n->m_valor = p;
    n->m_seg = m_taula[i];

    m_taula[i] = n;

    float fc = (float)total / (float)m_mida;

    if (fc >= factor_carrega)
    {
        redispersio(true);
    }
}

// θ(1)
template <typename Clau>
bool call_registry::diccionari<Clau>::cerca(const Clau &c, phone *&p) const
{
    //PRE: TRUE
    //POST: Phone obtindrá el valor de clau si existeix, si no será NULL
    nat i = hash(c);

    node_hash *n = m_taula[i];
    bool hi_es = false;

    while (n != NULL and not hi_es)
    {
        if (n->m_clau == c)
        {
            hi_es = true;
            p = n->m_valor;
        }
        else
        {
            n = n->m_seg;
        }
    }
    return hi_es;
}

// θ(1)
template <typename Clau>
bool call_registry::diccionari<Clau>::elimina(const Clau &c)
{
    //PRE: TRUE
    //POST: S'elimina del diccionari l'entrada corresponent a la Clau c
    nat i = hash(c);

    node_hash *nr = m_taula[i], *n = m_taula[i];
    bool hi_es = false;

    while (n != NULL and not hi_es)
    {
        if (n->m_clau == c)
        {
            if (nr == n)
            {
                m_taula[i] = n->m_seg;
            }
            else
            {
                nr->m_seg = n->m_seg;
            }

            if (m_taula[i] == NULL)
                --m_quants;

            --total;

            delete n->m_valor;
            delete n;

            n = NULL;

            hi_es = true;

            float fc = (float)total / (float)m_mida;

            if ((fc < (1 - factor_carrega)) and (m_mida > mida_inicial))
            {
                redispersio(false);
            }
        }
        else
        {
            nr = n;
            n = n->m_seg;
        }
    }

    return hi_es;
}

// θ(1)
template <typename Clau>
void call_registry::diccionari<Clau>::modifica(const Clau &c, phone *&p)
{
    //PRE: TRUE
    //POST: Es modifica el valor de p d'acord al valor del diccionari segons la clau
    nat i = hash(c);

    node_hash *n = m_taula[i];
    bool hi_es = false;

    while (n != NULL and not hi_es)
    {
        if (n->m_clau == c)
        {
            if (n == m_taula[i])
            {
                delete m_taula[i]->m_valor;

                m_taula[i]->m_valor = p;
            }
            else
            {
                delete n->m_valor;

                n->m_valor = p;
            }

            hi_es = true;
        }
        else
        {
            n = n->m_seg;
        }
    }
}

// θ(1)
template <typename Clau>
bool call_registry::diccionari<Clau>::guarda(vector<phone> &v) const
{
    //PRE: TRUE
    //POST: S'insereix al vector de phones v tots els phones. Si hi han repetits, es buida aquest vector
    bool repetits = false;
    nat i = 0;

    while (i < m_mida && !repetits)
    {
        if (m_taula[i] != NULL)
        {
            if (m_taula[i]->m_seg != NULL)
            {
                repetits = true;
            }
            v.push_back(*m_taula[i]->m_valor);
        }
        ++i;
    }
    if (repetits)
        v.clear();

    return repetits;
}

// θ(1)
template <typename Clau>
nat call_registry::diccionari<Clau>::elements() const
{
    //PRE: TRUE
    //POST: Retorna el número d'elements del diccionari
    return total;
}

// θ(1)
template <typename Clau>
bool call_registry::diccionari<Clau>::obtenir_phone(const Clau &c, node_hash *&n, node_hash *&nr)
{
    //PRE: TRUE
    //POST: Returna un bolea indicant si apareix al diccionari un node amb Clau c o no. Si apareix, assigna n al node que cumpleix la condició i nr al seu antedecessor. 
    nat i = hash(c);

    nr = n = m_taula[i];
    bool hi_es = false;

    while (n != NULL and not hi_es)
    {
        if (n->m_clau == c)
        {
            hi_es = true;
        }
        else
        {
            nr = n;
            n = n->m_seg;
        }
    }
    return hi_es;
}

// θ(2n)
template <typename Clau>
void call_registry::diccionari<Clau>::redispersio(bool duplica)
{
    //PRE: TRUE
    //POST: Reasigna els elements del diccionari segons la modificació de la taula. Aquesta modificació será de duplicar la mida de la taula si es supera el 75% de cárrega, i de divisió si es baixa del 25% de cárrega.
    nat mida_ant = m_mida;

    if (duplica)
        m_mida *= 2;
    else
        m_mida /= 2;

    node_hash **t = new node_hash *[m_mida];

    colisions = 0;
    m_quants = 0;

    for (nat i = 0; i < m_mida; ++i)
    {
        t[i] = NULL;
    }

    for (nat i = 0; i < mida_ant; ++i)
    {

        node_hash *n = m_taula[i];

        while (n != NULL)
        {
            node_hash *ant = n;

            n = n->m_seg;

            nat new_pos = hash(ant->m_clau);

            ant->m_seg = t[new_pos];

            t[new_pos] = ant;

            if (t[new_pos]->m_seg != NULL)
                ++colisions;
            else
                ++m_quants;
        }
    }

    delete[] m_taula;
    
    m_taula = t;

    if (duplica)
        ++redispersions;
    else
        ++shrinks;
}

// θ(1)
template <>
nat call_registry::diccionari<nat>::hash(nat c) const
{
    //PRE: TRUE
    //POST: Retorna la posició de la taula on anirá c
    c ^= (c << 13);
    c ^= (c >> 17);
    c ^= (c << 5);

    return c % m_mida;
}

// θ(c.length)
template <>
nat call_registry::diccionari<string>::hash(string c) const
{
    //PRE: TRUE
    //POST: Retorna la posició de la taula on anirá c
    nat n = 0;

    for (nat i = 0; i < c.length(); ++i)
    {
        n += c[i] * pow(2, i);
    }

    return n % m_mida;
}

template <typename Clau>
void call_registry::diccionari<Clau>::estadistiques()
{
    //PRE: TRUE
    //POST: Imprimeix un anàlisis exhaustiu del funcionament del diccionari
    cout << endl;
    cout << "Statistics..." << endl;
    cout << "-------------" << endl;
    cout << "Size: " << m_mida << endl;
    cout << "Rehashes: " << redispersions << endl;
    cout << "Shrinks: " << shrinks << endl;
    cout << "Elements: " << m_quants << endl;
    cout << "Collitions: " << colisions << endl;
    cout << "Total elements: " << total << endl;
    cout << "Ratio: " << (m_quants + colisions) / m_mida << endl;
    cout << "-------------" << endl;
}

// θ(2*n^2)
template <typename Clau>
bool call_registry::diccionari<Clau>::save(vector<phone> &v) const
{
    //PRE: TRUE
    //POST: Inserta el vector v tots el phones no repetits de forma poc eficient.
    for (nat i = 0; i < m_mida; ++i)
    {
        node_hash *n = m_taula[i];

        while (n != NULL)
        {
            if (n->m_valor->nom().length() > 0)
                v.push_back(*n->m_valor);

            n = n->m_seg;
        }
    }

    nat i = 0, j = 0;
    bool repetits = false;

    while (i < v.size() and !repetits)
    {
        while (j < v.size() and !repetits)
        {
            if (j != i)
            {
                if (v[i].nom() == v[j].nom())
                    repetits = true;
            }
            ++j;
        }

        j = 0;
        ++i;
    }

    return !repetits;
}

// ######################################################################################### //

// θ(n)
call_registry::call_registry() throw(error)
{
    //PRE: TRUE
    //POST: Crea un call_registry buit
    diccionari<nat> d_nums;
    //diccionari<string> d_noms;
}

// θ(n)
call_registry::call_registry(const call_registry &R) throw(error) : d_nums(R.d_nums) //,
                                                                                     //d_noms(R.d_noms)
{
    //PRE: TRUE
    //POST: El p.i. es idéntic a R
}

// θ(n)
call_registry &call_registry::operator=(const call_registry &R) throw(error)
{
    //PRE: TRUE
    //POST: Asigna al p.i. els valors de R
    d_nums = R.d_nums;
    //d_noms = R.d_noms;

    return *this;
}

// θ(2n)
call_registry::~call_registry() throw()
{
    //PRE: TRUE
    //POST: Elimina el p.i. de memória
    //d_nums.estadistiques();
    //d_noms.estadistiques();
}

// θ(1)
void call_registry::registra_trucada(nat num) throw(error)
{
    //PRE: TRUE.
    //POST: Registra una trucada al número donat. Si ja hi era, aumenta el comptador de trucades en 1, si no, crea una nova entrada al call_reigstry.
    phone *p = NULL;

    if (d_nums.cerca(num, p) and p != NULL)
    {
        ++*p;
    }
    else
    {
        p = new phone(num, "", 1);
        d_nums.insereix(num, p);
    }
}

// θ(1)
void call_registry::assigna_nom(nat num, const string &name) throw(error)
{
    //PRE: TRUE
    //POST: Assigna a aquest número el nóm. Si aquest número ja estaba registrat al call_registry, li assigna el nom. Si no hi era, crea una nova entrada amb freqüencia a 0.
    phone *p = NULL, *p2 = NULL;

    if (d_nums.cerca(num, p) and p != NULL)
    {
        try
        {
            p2 = new phone(p->numero(), name, p->frequencia());

            // phone *p3 = NULL;

            // if (d_noms.cerca(p->nom(), p3))
            //     d_noms.elimina(p->nom());

            //if (name.size() > 0)
            //    d_noms.insereix(name, p2);

            d_nums.modifica(num, p2);
        }
        catch (error e)
        {
            delete p2;
            throw error(e);
        }
    }
    else
    {
        try
        {
            p2 = new phone(num, name, 0);

            d_nums.insereix(num, p2);
            //if (name.size() > 0)
            //d_noms.insereix(name, p2);
        }
        catch (error e)
        {
            delete p2;
            throw error(e);
        }
    }
}

// θ(1)
void call_registry::elimina(nat num) throw(error)
{
    //PRE: TRUE
    //POST: Elimina l'entrada corresponent al teléfon dins el call_registry. Si aquesta entrada no existía, retorna un error.
    phone *p = NULL;

    d_nums.cerca(num, p);

    //d_noms.elimina(p->nom());

    //Modificacion
    if (!d_nums.elimina(num))
        throw error(ErrNumeroInexistent);
}

// θ(1)
bool call_registry::conte(nat num) const throw()
{
    //PRE: TRUE
    //POST: Retorna un boolea indicant si existeix una entrada del número proporcionat al call_registry
    phone *p = NULL;
    return d_nums.cerca(num, p);
}

// θ(1)
string call_registry::nom(nat num) const throw(error)
{
    //PRE: TRUE
    //POST: Retorna un string amb el nom associat a aquest número de teléfon. Si no te cap nom associat retorna un string buit i, si el teléfon no está registrat, retorna un error.
    phone *p = NULL;

    d_nums.cerca(num, p);

    if (p != NULL)
    {
        return p->nom();
    }
    else
    {
        throw error(ErrNumeroInexistent);
        return "";
    }
}

// θ(1)
nat call_registry::num_trucades(nat num) const throw(error)
{
    //PRE: TRUE
    //POST: Retorna un nat amb el número de trucades a aquest número de teléfon. Si no ha rebut cap trucada retorna 0 i, si el teléfon no está registrat, retorna un error.
    phone *p = NULL;

    d_nums.cerca(num, p);

    if (p != NULL)
    {
        return p->frequencia();
    }
    else
    {
        throw error(ErrNumeroInexistent);
        return 0;
    }
}

// θ(1)
bool call_registry::es_buit() const throw()
{
    //PRE: TRUE
    //POST: Retorna si aquest call_registry esta buit o no.
    return d_nums.elements() == 0;
}

// θ(1)
nat call_registry::num_entrades() const throw()
{
    //PRE: TRUE
    //POST: Retorna un nat amb les entrades del call_registry del p.i.
    return d_nums.elements();
}

// θ(n)
void call_registry::dump(vector<phone> &V) const throw(error)
{
    //PRE: TRUE
    //POST: Inserta en aquest vector tots el teléfons que tenen un nom assignat dins del call_registry.
    //if (d_noms.guarda(V))
    if (!d_nums.save(V))
        throw error(ErrNomRepetit);
}
// θ(n)
template <typename Clau>
bool call_registry::diccionari<Clau>::aux_aux_compare(diccionari<Clau> &aux)
{
    //PRE: TRUE
    //POST: Retorna un boolea indicant si el diccionari p i el p.i. són iguals.
    if ((m_mida == aux.m_mida) and (total == aux.total))
    {
        if (m_mida > 0 and aux.m_mida > 0)
        {
            for (nat i = 0; i < m_mida; ++i)
            {
                node_hash *n_cr = m_taula[i];
                node_hash *n_aux = aux.m_taula[i];
                while (n_cr != NULL and n_aux != NULL)
                {
                    if (n_cr->m_clau != n_aux->m_clau)
                    {
                        return false;
                    }
                    n_cr = n_cr->m_seg;
                    n_aux = n_aux->m_seg;
                }
            }
            return true;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}

// θ(n)
bool call_registry::aux_compare(diccionari<nat> &aux)
{
    //PRE: TRUE
    //POST: Retorna un boolea indicant si el diccionari p i el p.i. són iguals.
    return d_nums.aux_aux_compare(aux);
}

// θ(n)
bool call_registry::compare(call_registry &aux)
{
    //PRE: TRUE
    //POST: Retorna un boolea indicant si el call_registry aux i el p.i. són iguals.
    return aux_compare(aux.d_nums);
}