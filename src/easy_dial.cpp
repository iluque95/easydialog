#include "../incl/easy_dial.hpp"

//0(n * log(n))
easy_dial::easy_dial(const call_registry &R) throw(error) : m_arrel(NULL),
                                                            m_primer(NULL),
                                                            m_pi(NULL),
                                                            m_pref(""),
                                                            m_indef(true),
                                                            m_freq(0)
{
    vector<phone> v;
    R.dump(v);

    m_primer = new node;

    if (v.size() > 0)
    {
        mergeSort(v, 0, v.size() - 1);
        m_primer->m_p = v[0];
        //m_indef = false; QUITAR ???
    }

    for (nat i = 0; i < v.size(); ++i)
    {
        insereix(v[i].nom() + phone::ENDPREF, v[i]);
        m_freq += v[i].frequencia();
    }

    m_primer->m_val = m_arrel;

    m_pi = m_primer;
}

//0(n)
easy_dial::easy_dial(const easy_dial &D) throw(error) : m_pref(D.m_pref),
                                                        m_indef(D.m_indef),
                                                        m_freq(D.m_freq)
{
    //Bucle para el arbol
    m_arrel = crea_arbre(D.m_arrel);

    node *tmp = D.m_primer, *ant_tmp = NULL, *ant_aux = NULL;

    while (tmp != NULL)
    {
        ant_tmp = tmp;

        node *n = new node;

        n->m_val = tmp->m_val;
        n->m_p = tmp->m_p;
        n->m_ant = ant_tmp;
        n->m_seg = ant_aux;

        ant_aux = n;

        if (tmp == D.m_pi)
            m_pi = n;

        tmp = tmp->m_seg;
    }
}

//0(n)
easy_dial &easy_dial::operator=(const easy_dial &D) throw(error)
{

    if (this != &D)
    {
        easy_dial ed(D);

        node_tst *tst_tmp = m_arrel;

        m_arrel = ed.m_arrel;
        ed.m_arrel = tst_tmp;

        node *aux_tmp = m_primer;

        m_primer = ed.m_primer;
        ed.m_primer = aux_tmp;

        aux_tmp = m_pi;

        m_pi = ed.m_pi;
        ed.m_pi = aux_tmp;

        string str_tmp = m_pref;

        m_pref = ed.m_pref;
        ed.m_pref = str_tmp;

        bool b_tmp = m_indef;

        m_indef = ed.m_indef;
        ed.m_indef = b_tmp;

        double d_tmp = m_freq;

        m_freq = ed.m_freq;
        ed.m_freq = d_tmp;
    }

    return *this;
}

//0(n)
easy_dial::~easy_dial() throw()
{
    borra_arbre(m_arrel);
}

//0(1)
string easy_dial::inici() throw()
{
    m_pref = "";
    m_indef = false;

    if (m_primer != NULL)
    {
        /*
        node *ant = m_pi, *tmp = m_pi->m_seg;

        while (tmp != NULL)
        {
            ant->m_seg = NULL;
            ant = tmp;

            tmp = tmp->m_seg;

            delete ant; 
        }
        */
        m_pi = m_primer;
        return m_primer->m_p.nom();
    }
    else
        return "";
}

//0(1)
string easy_dial::seguent(char c) throw(error)
{
    vector<phone> v;

    string tmp;

    if (c == phone::ENDPREF)
    {
        if (m_pref.size() == 0) // ARREL
            return m_primer->m_p.nom();
    }

    tmp.reserve(m_pref.size() + 1);
    tmp.append(m_pref);
    tmp.push_back(c);

    comencen(v, tmp);

    if (m_pref.size() == 1 and v.size() > 0)
    {
        return v[1].nom();
    }
    

    return "";
}

//0(1)
string easy_dial::anterior() throw(error)
{
    if (m_indef)
        throw error(ErrPrefixIndef);
    else if (m_pi == m_primer)
    {
        m_indef = true;
        throw error(ErrNoHiHaAnterior);
    }

    node *tmp = m_pi;

    m_pi = m_pi->m_ant;
    m_pi->m_seg = NULL;

    delete tmp;

    m_pref.erase(m_pref.size() - 1);

    return m_pi->m_p.nom();
}

//0(1)
nat easy_dial::num_telf() const throw(error)
{

    if (m_indef)
        throw error(ErrPrefixIndef);

    if (m_pi->m_val == NULL)
    {
        throw error(ErrNoExisteixTelefon);
        return 0;
    }

    return m_pi->m_p.numero();
}

void easy_dial::comencen_aux(vector<string> &result, string str, node_tst *nt) const throw(error)
{

    if (nt != NULL)
    {
        if (nt->m_c == phone::ENDPREF)
        {
            result.push_back(str);
        }
        comencen_aux(result, str, nt->m_fesq);
        comencen_aux(result, str + nt->m_c, nt->m_fcen);
        comencen_aux(result, str, nt->m_fdret);
    }
}

typename easy_dial::node_tst *easy_dial::trobar_pref(node_tst *n, nat i, const string &k) const throw()
{
    node_tst *res = NULL;
    if (n != NULL)
    {
        if (i == k.length())
        {
            res = n;
        }
        else if (n->m_c > k[i])
        {
            res = trobar_pref(n->m_fesq, i, k);
        }
        else if (n->m_c < k[i])
        {
            res = trobar_pref(n->m_fdret, i, k);
        }
        else if (n->m_c == k[i])
        {
            res = trobar_pref(n->m_fcen, i + 1, k);
        }
    }
    return res;
}

void easy_dial::comencen(const string &pref, vector<string> &result) const throw(error)
{
    if (pref.size() > 0)
    {
        node_tst *n = trobar_pref(m_arrel, 0, pref);
        m_pi->m_val = n;

        if (n != NULL)
        {
            comencen_aux(result, pref, n);
        }
    }
    else
    {
        comencen_aux(result, "", m_arrel);
    }
}

double easy_dial::longitud_mitjana() const throw()
{
    //node_tst *n = m_arrel;
    //double freq = n->m_valor.frequencia() / m_freq;

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
        aux->m_fcen = crea_arbre(n->m_fcen);
        aux->m_fdret = crea_arbre(n->m_fdret);
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

// merges two subarrays of array[].
void easy_dial::merge(std::vector<phone> &arr, nat start, nat middle, nat end)
{

    std::vector<phone> leftArray(middle - start + 1);
    std::vector<phone> rightArray(end - middle);

    // fill in left array
    for (nat i = 0; i < leftArray.size(); ++i)
        leftArray[i] = arr[start + i];

    // fill in right array
    for (nat i = 0; i < rightArray.size(); ++i)
        rightArray[i] = arr[middle + 1 + i];

    /* Merge the temp arrays */

    // initial indexes of first and second subarrays
    nat leftIndex = 0, rightIndex = 0;

    // the index we will start at when adding the subarrays back into the main array
    nat currentIndex = start;

    // compare each index of the subarrays adding the lowest value to the currentIndex
    while (leftIndex < leftArray.size() && rightIndex < rightArray.size())
    {
        if (leftArray[leftIndex] >= rightArray[rightIndex])
        {
            arr[currentIndex] = leftArray[leftIndex];
            leftIndex++;
        }
        else
        {
            arr[currentIndex] = rightArray[rightIndex];
            rightIndex++;
        }
        currentIndex++;
    }

    // copy remaining elements of leftArray[] if any
    while (leftIndex < leftArray.size())
        arr[currentIndex++] = leftArray[leftIndex++];

    // copy remaining elements of rightArray[] if any
    while (rightIndex < rightArray.size())
        arr[currentIndex++] = rightArray[rightIndex++];
}

// main function that sorts array[start..end] using merge()
void easy_dial::mergeSort(std::vector<phone> &arr, nat start, nat end)
{
    // base case
    if (start < end)
    {
        // find the middle point
        nat middle = (start + end) / 2;

        mergeSort(arr, start, middle);   // sort first half
        mergeSort(arr, middle + 1, end); // sort second half

        // merge the sorted halves
        merge(arr, start, middle, end);
    }
}

void easy_dial::test(const vector<phone> &v)
{
    cout << "{";
    for (nat i = 0; i < v.size(); ++i)
        cout << " \033[0;33m[" << i << "]\033[0m => \"\033[0;34m" << v[i].nom() << " (" << v[i].frequencia() << ")\033[0m\"";

    cout << " }" << endl;
}

typename easy_dial::node_tst *easy_dial::buscar_pref(node_tst *n, const char &c)
{
    node_tst *ret = NULL;
    bool trobat = false;

    while (n != NULL and not trobat)
    {
        if (c > n->m_c)
        {
            n = n->m_fdret;
        }
        else if (c < n->m_c)
        {
            n = n->m_fesq;
        }
        else
        {
            ret = n;
            trobat = true;
        }
    }

    return ret;
}

void easy_dial::crea_node(node_tst *a)
{
    node *n = m_pi;

    if (m_pi->m_seg == NULL)
        m_pi->m_seg = new node;

    m_pi = m_pi->m_seg;

    m_pi->m_ant = n;

    m_pi->m_val = a;

    m_pi->m_seg = NULL;
}

void easy_dial::comencen_aux(vector<phone> &result, string str, node_tst *nt) const throw(error)
{

    if (nt != NULL)
    {
        if (nt->m_c == phone::ENDPREF)
        {
            result.push_back(nt->m_valor);
        }
        comencen_aux(result, str, nt->m_fesq);
        comencen_aux(result, str + nt->m_c, nt->m_fcen);
        comencen_aux(result, str, nt->m_fdret);
    }
}

void easy_dial::comencen(vector<phone> &result, const string &pref) const throw(error)
{
    if (pref.size() > 0)
    {
        node_tst *n = trobar_pref(m_pi->m_val, pref.size() - 1, pref);

        if (n != NULL)
        {
            comencen_aux(result, pref, n);
        }
    }
    else
    {
        comencen_aux(result, "", m_arrel);
    }
}