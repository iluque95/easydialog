#include "../incl/call_registry.hpp"
#include <bits/stdc++.h>

// θ(n)
template <typename Clau>
call_registry::diccionari<Clau>::diccionari() throw(error) : m_mida(200),
                                                             m_quants(0),
                                                             colisions(0),
                                                             redispersions(0),
                                                             total(0)
{

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
                                                                                total(d.total)
{

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
    }

    return *this;
}

// θ(n)
template <typename Clau>
call_registry::diccionari<Clau>::~diccionari() throw()
{

    for (nat i = 0; i < m_mida; ++i)
    {
        node_hash *prev = NULL;
        node_hash *act = m_taula[i];

        while (act != NULL)
        {
            prev = act;
            act = act->m_seg;

            delete prev;
        }
    }
}

// θ(1)
template <typename Clau>
void call_registry::diccionari<Clau>::insereix(const Clau &c, phone *&p)
{
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

    if ((m_quants / m_mida) >= factor_carrega)
    {
        redispersio();
    }
}

// θ(1)
template <typename Clau>
bool call_registry::diccionari<Clau>::cerca(const Clau &c, phone *&p) const
{
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

            delete n->m_valor;
            delete n;

            n = NULL;

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

// θ(1)
template <typename Clau>
void call_registry::diccionari<Clau>::modifica(const Clau &c, phone *&p)
{
    node_hash *n = NULL, *nr = NULL;

    if (obtenir_phone(c, n, nr) and n != NULL)
    {
        try
        {
            //delete n->m_valor;

            n->m_valor = p;
        }
        catch (error e)
        {
            throw error(e);
        }
    }
}

// θ(1)
template <typename Clau>
bool call_registry::diccionari<Clau>::guarda(vector<phone> &v) const
{
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
    return m_quants;
}

// θ(1)
template <typename Clau>
bool call_registry::diccionari<Clau>::obtenir_phone(const Clau &c, node_hash *&n, node_hash *&nr)
{
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
void call_registry::diccionari<Clau>::redispersio()
{

    nat mida_ant = m_mida;

    m_mida *= 2;

    node_hash **t = new node_hash *[m_mida];

    colisions = 0;
    m_quants = 0;
    total = 0;

    for (nat i = 0; i < m_mida; ++i)
    {
        t[i] = NULL;
    }

    for (nat i = 0; i < mida_ant; ++i)
    {

        if (m_taula[i] != NULL)
        {
            nat new_pos = hash(m_taula[i]->m_clau);

            if (t[new_pos] == NULL)
                ++m_quants;
            else
                ++colisions;

            ++total;

            node_hash *tmp = new node_hash;

            tmp->m_clau = m_taula[i]->m_clau;
            tmp->m_valor = new phone(*m_taula[i]->m_valor);
            tmp->m_seg = t[new_pos];
            t[new_pos] = tmp;

            node_hash *n = m_taula[i]->m_seg;

            delete m_taula[i];

            while (n != NULL)
            {
                node_hash *ant = n;

                if (t[new_pos] == NULL)
                    ++m_quants;
                else
                    ++colisions;

                ++total;

                node_hash *tmp = new node_hash;

                new_pos = hash(tmp->m_clau);

                tmp->m_clau = n->m_clau;
                tmp->m_valor = new phone(*n->m_valor);
                tmp->m_seg = t[new_pos];
                t[new_pos] = tmp;

                n = n->m_seg;

                delete ant;
            }

            m_taula[i] = NULL;
        }
    }

    node_hash **tmp = m_taula;

    m_taula = t;
    t = tmp;

    ++redispersions;
}

// θ(1)
template <>
nat call_registry::diccionari<nat>::hash(nat c) const
{
    c ^= (c << 13);
    c ^= (c >> 17);
    c ^= (c << 5);

    return c % m_mida;
}

// θ(c.length)
template <>
nat call_registry::diccionari<string>::hash(string c) const
{
    nat n = 0;

    for (nat i = 0; i < c.length(); ++i)
    {
        n += c[i] * pow(2, i);
    }

    return n % m_mida;
    ;
}

template <typename Clau>
void call_registry::diccionari<Clau>::estadistiques()
{
    cout << endl;
    cout << "Statistics..." << endl;
    cout << "-------------" << endl;
    cout << "Size: " << m_mida << endl;
    cout << "Rehashes: " << redispersions << endl;
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
    diccionari<nat> d_nums;
    //diccionari<string> d_noms;
}

// θ(n)
call_registry::call_registry(const call_registry &R) throw(error) : d_nums(R.d_nums) //,
                                                                                     //d_noms(R.d_noms)
{
}

// θ(n)
call_registry &call_registry::operator=(const call_registry &R) throw(error)
{
    d_nums = R.d_nums;
    //d_noms = R.d_noms;

    return *this;
}

// θ(2n)
call_registry::~call_registry() throw()
{
    //d_nums.estadistiques();
    //d_noms.estadistiques();
}

// θ(1)
void call_registry::registra_trucada(nat num) throw(error)
{
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
    phone *p = NULL;
    return d_nums.cerca(num, p);
}

// θ(1)
string call_registry::nom(nat num) const throw(error)
{
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
    return d_nums.elements() == 0;
}

// θ(1)
nat call_registry::num_entrades() const throw()
{
    return d_nums.elements();
}

// θ(n)
void call_registry::dump(vector<phone> &V) const throw(error)
{
    //if (d_noms.guarda(V))
    if (!d_nums.save(V))
        throw error(ErrNomRepetit);
}