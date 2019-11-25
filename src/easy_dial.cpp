#include "../incl/easy_dial.hpp"

easy_dial::easy_dial(const call_registry &R) throw(error)
{
    vector<phone> v;
    R.dump(v);

    for (nat i=0; i<v.size(); ++i)
    {
        insereix(v[i].nom(), v[i]);
    }
}

easy_dial::easy_dial(const easy_dial &D) throw(error)
{
}

easy_dial &easy_dial::operator=(const easy_dial &D) throw(error)
{
    return *this;
}

easy_dial::~easy_dial() throw()
{
}

string easy_dial::inici() throw()
{
    m_primer = new node;

    m_primer->m_val = NULL;
    m_primer->m_ant = m_primer->m_seg = NULL;

    m_pi = m_primer;

    m_pref = "";

    return m_pref;
}

string easy_dial::seguent(char c) throw(error)
{

    if (m_pi->m_val != NULL)
    {
        m_pi->m_seg = new node;
        m_pi->m_seg->m_val = m_arrel;
        m_pi->m_seg->m_ant = m_pi;
        m_pi->m_seg->m_seg = NULL;

        m_pref.push_back(c);
    }
    else
    {
        m_indef = true;
        m_pref = "";
        throw error(ErrPrefixIndef);
    }

    return m_pref;
}

string easy_dial::anterior() throw(error)
{
    if (m_indef)
        throw error(ErrPrefixIndef);

    else if (m_pi == m_primer)
        throw error(ErrNoHiHaAnterior);

    node *tmp = m_pi;

    m_pi = m_pi->m_ant;
    m_pi->m_seg = NULL;

    delete tmp;

    m_pref.erase(m_pref.size() - 1);

    return m_pref;
}

//0(1)
nat easy_dial::num_telf() const throw(error)
{

    if (m_indef)
        throw error(ErrPrefixIndef);

    if (m_arrel != NULL)
    {
        return m_pi->m_val->m_telf->numero();
    }
    else
    {
        throw error(ErrNoExisteixTelefon);
        return 0;
    }
}

void easy_dial::comencen(const string &pref, vector<string> &result) const throw(error)
{
}

double easy_dial::longitud_mitjana() const throw()
{
    return 0;
}

void easy_dial::consulta(const string &k, bool &hi_es, phone *&v) const throw()
{
    node_tst *n = rconsulta(m_arrel, 0, k);
    if (n == NULL)
    {
        hi_es = false;
    }
    else
    {
        v = n->m_telf;
        hi_es = true;
    }
}

void easy_dial::insereix(const string &k, const phone &v) throw(error)
{
    m_arrel = rinsereix(m_arrel, 0, k, v);
}

typename easy_dial::node_tst *easy_dial::rconsulta(node_tst *n, nat i, const string &k) const throw()
{
    node_tst *res = NULL;
    if (n != NULL)
    {
        if (i == k.length() and n->m_c == phone::ENDPREF)
        {
            res = n;
        }
        else if (n->m_c > k[i])
        {
            res = rconsulta(n->m_fesq, i, k);
        }
        else if (n->m_c < k[i])
        {
            res = rconsulta(n->m_fdret, i, k);
        }
        else if (n->m_c == k[i])
        {
            res = rconsulta(n->m_fcen, i + 1, k);
        }
    }
    return res;
}

typename easy_dial::node_tst *easy_dial::rinsereix(node_tst *n, nat i, const string &k, const phone &v) throw(error)
{
    if (n == NULL)
    {
        n = new node_tst;
        n->m_fesq = n->m_fdret = n->m_fcen = NULL;
        n->m_c = k[i];
        try
        {
            if (i < k.length() - 1)
            {
                n->m_fcen = rinsereix(n->m_fcen, i + 1, k, v);
            }
            else
            { // i == k.length()-1; k[i] == Simbol()
                n->m_telf = new phone(v);
            }
        }
        catch (error)
        {
            delete n;
            throw;
        }
    }
    else
    {
        if (n->m_c > k[i])
        {
            n->m_fesq = rinsereix(n->m_fesq, i, k, v);
        }
        else if (n->m_c < k[i])
        {
            n->m_fdret = rinsereix(n->m_fdret, i, k, v);
        }
        else
        { // (n->m_c == k[i])
            n->m_fcen = rinsereix(n->m_fcen, i + 1, k, v);
        }
    }
    return n;
}