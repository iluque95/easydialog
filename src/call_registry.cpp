#include "../incl/call_registry.hpp"

// θ(n)
template <typename Clau>
call_registry::diccionari<Clau>::diccionari() throw(error) : m_mida(100),
                                                             m_quants(0),
                                                             colisions(0),
                                                             redispersions(0)
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
                                                                                m_quants(d.m_quants)
{

    m_taula = new node_hash *[m_mida];

    for (nat i = 0; i < m_mida; ++i)
    {
        m_taula[i] = new node_hash;
        node_hash *n = m_taula[i];

        m_taula[i]->m_clau = d.m_taula[i]->m_clau;
        m_taula[i]->m_valor = new phone(*d.m_taula[i]->m_valor);

        while (n->m_seg != NULL)
        {
            node_hash *aux = new node_hash;

            aux->m_clau = n->m_seg->m_clau;
            aux->m_valor = new phone(*n->m_seg->m_valor);
            n->m_seg = aux;
            n = aux;
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

    delete m_taula;
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
    node_hash *n = NULL, *nr = NULL;

    if (obtenir_phone(c, n, nr) and n != NULL)
    {
        if (nr != n)
        {
            nr->m_seg = n->m_seg;
        }

        delete n;

        return true;
    }

    return false;
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
            phone *ant = n->m_valor;

            n->m_valor = p;
            delete ant;
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

    n = m_taula[i];
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

// θ(n)
template <typename Clau>
void call_registry::diccionari<Clau>::redispersio()
{

    node_hash **t = new node_hash *[m_mida * 2];

    for (nat i = 0; i < m_mida; ++i)
    {
        if (m_taula[i] != NULL)
        {
            node_hash *n = m_taula[i];
            int new_pos = hash(n->m_clau);
            t[new_pos] = m_taula[i];
            t[new_pos]->m_seg = NULL;

            while (n->m_seg != NULL)
            {
                int new_pos = hash(n->m_seg->m_clau);
                node_hash *aux = new node_hash;

                aux->m_clau = n->m_seg->m_clau;
                aux->m_valor = n->m_seg->m_valor;
                aux->m_seg = t[new_pos];
                t[new_pos] = aux;
                n = n->m_seg;
            }

            m_taula[i] = NULL;
        }
    }

    for (nat i = m_mida; i < (m_mida * 2); ++i)
    {
        t[i] = NULL;
    }

    m_mida *= 2;

    node_hash **tmp = m_taula;

    m_taula = t;
    t = tmp;

    ++redispersions;
}

// θ(1)
template <>
nat call_registry::diccionari<nat>::hash(nat c) const
{

    nat key = c;
    key ^= (key << 13);
    key ^= (key >> 17);
    key ^= (key << 5);
    key %= m_mida;
    return key;

    /*long y = ((c * c * MULT) << 20) >> 4;

    y %= m_mida;

    return y;*/
}

// θ(c.length)
template <>
nat call_registry::diccionari<string>::hash(string c) const
{
    nat n = 0;
    for (nat i = 0; i < c.length(); ++i)
    {
        n = n + c[i] * i;
    }
    return n % m_mida;
}

template <typename Clau>
void call_registry::diccionari<Clau>::estadistiques()
{
    cout << endl;
    cout << "Statistics..." << endl;
    cout << "-------------" << endl;
    cout << "Collitions: " << colisions << endl;
    cout << "Rehashes: " << redispersions << endl;
    cout << "Size: " << m_mida << endl;
    cout << "Elements: " << m_quants << endl;
    cout << "-------------" << endl;
}

// ######################################################################################### //

// θ(n)
call_registry::call_registry() throw(error)
{
    diccionari<nat> d_nums;
    diccionari<string> d_noms;
}

// θ(n)
call_registry::call_registry(const call_registry &R) throw(error) : d_nums(R.d_nums),
                                                                    d_noms(R.d_noms)
{
}

// θ(n)
call_registry &call_registry::operator=(const call_registry &R) throw(error)
{
    d_nums = R.d_nums;
    d_noms = R.d_noms;

    return *this;
}

// θ(2n)
call_registry::~call_registry() throw()
{
    d_nums.estadistiques();
    d_noms.estadistiques();
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
        p2 = new phone(p->numero(), name, p->frequencia());

        phone *p3 = NULL;

        if (d_noms.cerca(p->nom(), p3))
            d_noms.elimina(p->nom());

        if (name.size() > 0)
            d_noms.insereix(name, p2);

        d_nums.modifica(num, p2);
    }
    else
    {
        p2 = new phone(num, name, 0);

        d_nums.insereix(num, p2);
        d_noms.insereix(name, p2);
    }
}

// θ(1)
void call_registry::elimina(nat num) throw(error)
{

    phone *p = NULL;

    d_nums.cerca(num, p);

    d_noms.elimina(p->nom());

    if (!d_nums.elimina(num))
        throw error(ErrNumeroInexistent, nom_mod, MsgErrNumeroInexistent);
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
        throw error(ErrNumeroInexistent, nom_mod, MsgErrNumeroInexistent);
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
        throw error(ErrNumeroInexistent, nom_mod, MsgErrNumeroInexistent);
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
    if (d_noms.guarda(V))
        throw error(ErrNomRepetit, nom_mod, MsgErrNomRepetit);
}