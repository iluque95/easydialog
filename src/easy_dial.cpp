#include "../incl/easy_dial.hpp"

easy_dial::easy_dial(const call_registry &R) throw(error)
{
    vector<phone> v;
    R.dump(v);

    for (nat i = 0; i < v.size(); ++i)
    {
        insereix(v[i].nom(), v[i]);
    }

    //Constructor del arbol
}

easy_dial::easy_dial(const easy_dial &D) throw(error)
{
    //Bucle para el arbol
    m_arrel = crea_arbre(D.m_arrel);

    // FIXME: CREAR NODO ANTES DE ASIGNAR.
    //Bucle para la linked list

    /*
    node n = D.m_pi;
    while (n->m_seg != NULL)
    {
        node_tst *m_val = n->m_val;
        node *m_ant = n->m_ant;
        node *m_seg = n->m_seg;
        n = n->m_seg;
    }

    m_primer = D.m_primer;
    m_pi = D.m_pi;
    m_pref = D.m_pref;
    m_indef = D.m_indef;
    */
}

easy_dial &easy_dial::operator=(const easy_dial &D) throw(error)
{
    return *this;
}

easy_dial::~easy_dial() throw()
{
    borra_arbre(m_arrel);
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
        //Avanzar un paso en el recorrido del
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
        return m_pi->m_val->m_valor.numero();
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
    //Aquí sería obtener la frecuencia del primer elemento, y luego recorrer todo el arbol sumando frecuencias
    return 0;
}

void easy_dial::consulta(const string &k, bool &hi_es, phone &v) const throw()
{
    node_tst *n = rconsulta(m_arrel, 0, k);
    if (n == NULL)
    {
        hi_es = false;
    }
    else
    {
        v = n->m_valor;
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
                n->m_valor = v;
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

easy_dial::node_tst *easy_dial::crea_arbre(node_tst *n)
{
    node_tst *aux = NULL;
    if (n != NULL)
    {
        aux = new node_tst;

        aux->m_fesq = crea_arbre(n->m_fesq);
        aux->m_fdret = crea_arbre(n->m_fdret);
        aux->m_fcen = crea_arbre(n->m_fcen);
        aux->m_c = n->m_c;
        aux->m_valor = n->m_valor;

        return aux;
    }
    
    return aux;
}

void easy_dial::borra_arbre(node_tst *n)
{

    if (n != NULL)
    {
        borra_arbre(n->m_fesq);
        borra_arbre(n->m_fdret);
        borra_arbre(n->m_fcen);

        delete n;
    }
}