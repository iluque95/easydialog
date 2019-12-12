#include "../incl/easy_dial.hpp"

//0(2n * log(n))
easy_dial::easy_dial(const call_registry &R) throw(error) : m_arrel(NULL),
                                                            m_primer(NULL),
                                                            m_pi(NULL),
                                                            m_pref(""),
                                                            m_indef(true),
                                                            m_freq(0)
{
    vector<phone> v;
    R.dump(v);

    if (v.size() > 0)
    {
        mergeSort(v, 0, v.size() - 1);

        m_primer = new node;

        m_primer->m_seg = m_primer->m_ant = NULL;

        m_primer->m_p = v[0];

        for (nat i = 0; i < v.size(); ++i)
        {
            insereix(v[i].nom() + phone::ENDPREF, v[i]);
            m_freq += v[i].frequencia();
        }

        // Calculem la longitud mitjana un cop sabem la freqüència total.
        m_freq = calcula_longitud(m_arrel) / m_freq;

        m_primer->m_val = m_arrel;

        m_pi = m_primer;
    }
}

//0(n)
easy_dial::easy_dial(const easy_dial &D) throw(error) : m_pref(D.m_pref),
                                                        m_indef(D.m_indef),
                                                        m_freq(D.m_freq)
{
    //Bucle para el arbol
    m_arrel = crea_arbre(D.m_arrel);

    copia_estructura_aux(D.m_primer, D.m_pi);
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

    borra_estructura_aux(m_primer);
}

//0(1)
string easy_dial::inici() throw()
{
    m_pref = "";
    m_indef = false;

    if (m_primer != NULL)
    {
        m_pi = m_primer;

        return m_pi->m_p.nom();
    }
    else
        return "";
}

//0(1)
string easy_dial::seguent(char c) throw(error)
{

    if (m_indef)
    {
        throw error(ErrPrefixIndef);
        return "";
    }

    if (m_pi == NULL or m_pi->m_p.nom().size() == 0)
    {
        m_indef = true;
        m_pref = "";
        throw error(ErrPrefixIndef);
    }

    string tmp;
    bool complet = false;

    if (c == phone::ENDPREF)
    {
        if (m_pref.size() == 0) // ARREL
        {
            crea_node(NULL);
            return "";
        }
        else
        {
            complet = true;
        }
    }

    tmp.reserve(m_pref.size() + 1);
    tmp.append(m_pref);
    tmp.push_back(c);

    comencen_amb(tmp, complet);

    if (m_pi->m_val != NULL and m_pi->m_p.nom().size() > 0)
    {
        m_pref.push_back(c);

        return m_pi->m_p.nom();
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

    if (m_pref.size() > 0)
        m_pref.erase(m_pref.size() - 1);

    return m_pi->m_p.nom();
}

//0(1)
nat easy_dial::num_telf() const throw(error)
{

    if (m_indef)
        throw error(ErrPrefixIndef);

    if (m_pi == NULL or m_pi->m_p.nom().size() == 0)
    {
        throw error(ErrNoExisteixTelefon);
        return ErrNoExisteixTelefon;
    }

    return m_pi->m_p.numero();
}

//0(n)
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

//0(1)
void easy_dial::comencen_major(phone &result, string str, node_tst *nt) const throw(error)
{

    if (nt != NULL)
    {
        if (nt->m_c == phone::ENDPREF)
        {
            if (not repetit(str) and nt->m_valor > result)
                result = nt->m_valor;
        }

        comencen_major(result, str + nt->m_c, nt->m_fcen);
        comencen_major(result, str, nt->m_fdret);
        comencen_major(result, str, nt->m_fesq);
    }
}

//0(1)
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
            if (n->m_c == phone::ENDPREF)
                res = trobar_pref(n, i + 1, k);
            else
                res = trobar_pref(n->m_fcen, i + 1, k);
        }
    }
    return res;
}

//0(1)
void easy_dial::comencen_amb(const string &pref, bool complet) throw(error)
{
    if (pref.size() > 0)
    {
        node_tst *n = trobar_pref(m_pi->m_val, pref.size() - 1, pref);

        if (n != NULL)
        {

            phone p;

            if (not complet)
            {
                crea_node(n);
                comencen_major(p, pref, n);
                m_pi->m_p = p;
            }
            else
            {

                // Ha estat visitat?
                if (m_pi->m_p.nom() == n->m_valor.nom() or repetit(n->m_valor.nom()))
                {
                    crea_node(NULL);
                    m_pi->m_p = p;
                }
                else
                {
                    crea_node(n);
                    m_pi->m_p = n->m_valor;
                }
            }
        }
        else
        {
            crea_node(NULL);
        }
    }
    else
    {
        phone p;
        comencen_major(p, "", m_arrel);
    }
}

//0(n)
void easy_dial::comencen(const string &pref, vector<string> &result) const throw(error)
{
    if (pref.size() > 0)
    {
        node_tst *n = trobar_pref(m_arrel, 0, pref);

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

//0(1)
double easy_dial::longitud_mitjana() const throw()
{
    return m_freq;
}

void easy_dial::insereix(const string &k, const phone &v) throw(error)
{
    m_arrel = rinsereix(m_arrel, 0, k, v);
}

//0(log K.length)
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

//0(n)
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

//0(n)
void easy_dial::borra_arbre(node_tst *&n)
{

    if (n != NULL)
    {
        borra_arbre(n->m_fesq);
        borra_arbre(n->m_fdret);
        borra_arbre(n->m_fcen);

        delete n;
        n = NULL;
    }
}

//0(log n)
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

//0(log n)
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

void easy_dial::crea_node(node_tst *a)
{
    node *n = m_pi;

    if (m_pi->m_seg == NULL)
        m_pi->m_seg = new node;

    m_pi = m_pi->m_seg;

    m_pi->m_ant = n;

    n->m_seg = m_pi;

    m_pi->m_val = a;

    m_pi->m_seg = NULL;
}

//0(1)
bool easy_dial::repetit(const string &str) const
{
    node *tmp = m_primer;

    bool visitat = false;

    while (tmp != m_pi and not visitat)
    {
        if (str == tmp->m_p.nom())
            visitat = true;
        else
            tmp = tmp->m_seg;
    }

    return visitat;
}

//0(1)
typename easy_dial::node_tst *easy_dial::max(node_tst *fesq, node_tst *fdret)
{

    node_tst *tmpA = fesq, *tmpB = fdret;

    while (tmpA->m_c != phone::ENDPREF)
    {
        tmpA = tmpA->m_fcen;
    }

    while (tmpB->m_c != phone::ENDPREF)
    {
        tmpB = tmpB->m_fcen;
    }

    if (tmpA->m_valor > tmpB->m_valor)
        return fesq;
    else
        return fdret;
}

//0(n)
nat easy_dial::calcula_longitud(node_tst *nt, nat freq)
{
    nat total = 0;
    if (nt != NULL)
    {
        if (nt->m_c == phone::ENDPREF)
        {
            total = nt->m_valor.frequencia() * freq;
        }

        if (nt->m_fesq != NULL and nt->m_fdret != NULL)
        {
            node_tst *mx = max(nt->m_fesq, nt->m_fdret);
            node_tst *mn = ((mx == nt->m_fesq) ? nt->m_fdret : nt->m_fesq);

            total += calcula_longitud(mx, freq + 1);

            if (mn->m_c == phone::ENDPREF)
                total += calcula_longitud(mn, freq + 2);
            else
                total += calcula_longitud(mn, freq + 1);
        }
        else
        {
            total += calcula_longitud(nt->m_fdret, freq + 1);
            total += calcula_longitud(nt->m_fesq, freq + 1);
        }

        total += calcula_longitud(nt->m_fcen, freq);
    }

    return total;
}

//0(n)
nat easy_dial::calcula_longitud(node_tst *nt)
{
    return calcula_longitud(m_arrel, 0);
}

//0(n)
void easy_dial::copia_estructura_aux(node *n, node *d_m_pi)
{
    node *tmp = n, *ant_tmp = NULL;

    while (tmp != NULL)
    {
        node *aux = new node;

        if (ant_tmp != NULL)
            ant_tmp->m_seg = aux;

        aux->m_val = tmp->m_val;
        aux->m_p = tmp->m_p;
        aux->m_ant = ant_tmp;
        aux->m_seg = NULL;

        ant_tmp = tmp;

        if (tmp == d_m_pi)
            m_pi = n;

        tmp = tmp->m_seg;
    }
}

//0(n)
void easy_dial::borra_estructura_aux(node *&n)
{
    if (n != NULL)
    {
        borra_estructura_aux(n->m_seg);
        delete n;
        n = NULL;
    }
}