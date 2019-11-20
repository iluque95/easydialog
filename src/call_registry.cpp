#include "../incl/call_registry.hpp"

// θ(n)
call_registry::call_registry() throw(error) : m_mida(2),
                                              m_quants(0)

{
    m_taula = new node_hash<nat, phone> *[m_mida];

    for (nat i = 0; i < m_mida; ++i)
    {
        m_taula[i] = NULL;
    }
}

// θ(n)
// TODO: Add next node_hash.
call_registry::call_registry(const call_registry &R) throw(error) : m_mida(R.m_mida),
                                                                    m_quants(R.m_quants)
{
    m_taula = new node_hash<nat, phone> *[m_mida];

    for (nat i = 0; i < m_mida; ++i)
    {
        m_taula[i] = new node_hash<nat, phone>;
        node_hash<nat, phone> n = m_taula[i];

        m_taula[i]->m_clau = R.m_taula[i]->m_clau;
        m_taula[i]->m_valor = new phone(*R.m_taula[i]->m_valor);

        while (n->m_seg != NULL)
        {
            node_hash<nat, phone> aux = new node_hash<nat, phone>;

            aux->m_clau = n->m_seg->m_clau;
            aux->m_valor = new phone(*n->m_seg->m_valor);
            n->m_seg = aux;
            n = aux;
        }
    }
}

// θ(n)
call_registry &call_registry::operator=(const call_registry &R) throw(error)
{
    if (this != &R)
    {
        call_registry cr(R);

        node_hash<nat, phone> **tmp = m_taula;

        m_taula = cr.m_taula;
        cr.m_taula = tmp;

        nat val = m_mida;

        m_mida = cr.m_mida;
        cr.m_mida = val;

        val = m_quants;

        m_quants = cr.m_quants;
        cr.m_quants = val;
    }

    return *this;
}

// θ(n)
call_registry::~call_registry() throw()
{
    for (nat i = 0; i < m_mida; ++i)
    {
        node_hash<nat, phone> *prev = NULL;
        node_hash<nat, phone> *act = m_taula[i];

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
void call_registry::registra_trucada(nat num) throw(error)
{
    node_hash<nat, phone> *p = NULL, *pr = NULL;

    if (obtenir_phone(num, p, pr) and p != NULL)
    {
        try
        {
            ++p->m_valor;
        }
        catch (error e)
        {
            throw error(e);
        }
    }
    else
    {
        afegeix_entrada(num, "", 1);
    }
}

// θ(1)
void call_registry::assigna_nom(nat num, const string &name) throw(error)
{
    node_hash<nat, phone> *p = NULL, *pr = NULL;

    if (obtenir_phone(num, p, pr) and p != NULL)
    {
        phone *ant = p->m_valor;
        try
        {

            p->m_valor = new phone(num, name, ant->frequencia());
            delete ant;
        }
        catch (error e)
        {
            throw error(e);
            delete p->m_valor;
        }
    }
    else
    {
        afegeix_entrada(num, name, 0);
    }
}

// θ(1)
void call_registry::elimina(nat num) throw(error)
{
    node_hash<nat, phone> *p = NULL, *pr = NULL;

    if (obtenir_phone(num, p, pr) and p != NULL)
    {
        if (pr != p)
        {
            pr->m_seg = p->m_seg;
        }

        delete p;
    }
    else
    {
        throw error(ErrNumeroInexistent, nom_mod, MsgErrNumeroInexistent);
    }
}

// θ(1)
bool call_registry::conte(nat num) const throw()
{
    nat i = hash(num);

    node_hash<nat, phone> *p = m_taula[i];
    bool hi_es = false;

    while (p != NULL and not hi_es)
    {
        if (p->m_clau == num)
        {
            hi_es = true;
        }
        else
        {
            p = p->m_seg;
        }
    }
    return hi_es;
}

// θ(1)
string call_registry::nom(nat num) const throw(error)
{
    nat i = hash(num);

    node_hash<nat, phone> *p = m_taula[i];
    bool hi_es = false;

    while (p != NULL and not hi_es)
    {
        if (p->m_clau == num)
        {
            hi_es = true;
        }
        else
        {
            p = p->m_seg;
        }
    }

    if (hi_es and p != NULL)
    {
        return p->m_valor->nom();
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
    nat i = hash(num);

    node_hash<nat, phone> *p = m_taula[i];
    bool hi_es = false;

    while (p != NULL and not hi_es)
    {
        if (p->m_clau == num)
        {
            hi_es = true;
        }
        else
        {
            p = p->m_seg;
        }
    }

    if (hi_es and p != NULL)
    {
        return p->m_valor->frequencia();
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
    return m_quants == 0;
}

// θ(1)
nat call_registry::num_entrades() const throw()
{
    return m_quants;
}

// θ(n)
void call_registry::dump(vector<phone> &V) const throw(error)
{
}

// θ(1)
nat call_registry::hash(nat num) const
{
    num = ((num >> 16) ^ num) * 0x45d9f3b;
    num = ((num >> 16) ^ num) * 0x45d9f3b;
    num = (num >> 16) ^ num;

    num %= m_mida;

    return num;
}

// θ(1)
void call_registry::afegeix_entrada(const nat &num, const string &nom, nat compt)
{
    nat i = hash(num);

    if (m_taula[i] == NULL)
        ++m_quants;
    else
        ++colisions;

    node_hash<nat, phone> *n = new node_hash<nat, phone>;

    n->m_clau = num;
    n->m_valor = new phone(num, nom, compt);
    n->m_seg = m_taula[i];

    m_taula[i] = n;

    if ((m_quants / m_mida) >= factor_carrega)
    {
        redispersio();
    }
}

// θ(n)
void call_registry::redispersio()
{

    m_mida *= 2;

    node_hash<nat, phone> **t = new node_hash<nat, phone> *[m_mida];

    for (nat i = 0; i < m_mida; ++i)
    {
        if (m_taula[i] != NULL)
        {
            int new_pos = hash(n->m_clau);
            node_hash<nat, phone> *n = m_taula[i];
            t[new_pos] = m_taula[i];
            t[new_pos]->m_seg = NULL;

            while (n->m_seg != NULL)
            {
                int new_pos = hash(n->m_seg->m_clau);
                node_hash<nat, phone> *aux = new node_hash<nat, phone>;

                aux->m_clau = n->m_seg->m_clau;
                aux->m_valor = n->m_seg->m_valor
                aux->m_seg = t[new_pos];
                t[new_pos] = aux;
                n = n->m_seg;
            }
            
            m_taula[i] = NULL;
        }
    }

    node_hash<nat, phone> **tmp = m_taula;

    m_taula = t;
    t = tmp;

    ++redispersions;
}

// θ(1)
bool call_registry::obtenir_phone(const nat &num, node_hash<nat, phone> *&p, node_hash<nat, phone> *&pr)
{
    nat i = hash(num);

    p = m_taula[i];
    bool hi_es = false;

    while (p != NULL and not hi_es)
    {
        if (p->m_clau == num)
        {
            hi_es = true;
        }
        else
        {
            pr = p;
            p = p->m_seg;
        }
    }
    return hi_es;
}