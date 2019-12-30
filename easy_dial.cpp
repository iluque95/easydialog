#include "easy_dial.hpp"

//0(2n * log(n))
easy_dial::easy_dial(const call_registry &R) throw(error) : m_arrel(NULL),
                                                            m_primer(NULL),
                                                            m_pi(NULL),
                                                            m_pref(""),
                                                            m_indef(true),
                                                            m_freq(0)
{
    //PRE: TRUE
    //POST: Crea un easy_dial
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
easy_dial::easy_dial(const easy_dial &D) throw(error) : m_arrel(NULL),
                                                        m_primer(NULL),
                                                        m_pi(NULL),
                                                        m_pref(D.m_pref),
                                                        m_indef(D.m_indef),
                                                        m_freq(D.m_freq)
{
    //PRE: TRUE
    //POST: El p.i. és un easy_dial idéntic a D
    //Bucle para el arbol
    m_arrel = crea_arbre(D.m_arrel);

    copia_estructura_aux(D.m_primer, D.m_pi);
}

//0(n)
easy_dial &easy_dial::operator=(const easy_dial &D) throw(error)
{
    //PRE: TRUE
    //POST: S'assignen al p.i. els valors de D
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
    //PRE: TRUE
    //POST: Elimina de memoria el easy_dial del p.i.
    borra_arbre(m_arrel);

    borra_estructura_aux(m_primer);
}

//0(n)
easy_dial::node_tst *easy_dial::crea_arbre(node_tst *n)
{
    //PRE: TRUE
    //POST: Retorna un node_tst apuntant a l'arrel de l'abre creat.
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
    //PRE: TRUE
    //POST: Elimina de memoria tots els elements del arbre amb arrel n
    if (n != NULL)
    {
        borra_arbre(n->m_fesq);
        borra_arbre(n->m_fdret);
        borra_arbre(n->m_fcen);

        delete n;
        n = NULL;
    }
}

//0(n)
void easy_dial::copia_estructura_aux(node *n, node *d_m_pi)
{
    //PRE: TRUE
    //POST: Realitza una replica d'un node i el consecuent arbre en un altre node
    node *tmp = n, *ant_tmp = NULL, *aux = NULL;

    bool primer = true;

    while (tmp != NULL)
    {
        if (primer)
        {
            m_primer = tmp;
            primer = not primer;
            aux = new node;
        }
        else
        {
            aux->m_seg = new node;
            aux = aux->m_seg;
        }

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
    //PRE: TRUE
    //POST: Elimina de memoria tots els elements del arbre amb arrel n
    if (n != NULL)
    {
        borra_estructura_aux(n->m_seg);
        delete n;
        n = NULL;
    }
}

//0(1)
void easy_dial::crea_node(node_tst *a)
{
    //PRE: TRUE
    //POST: Crea un node amb valor a
    node *n = m_pi;

    if (m_pi->m_seg == NULL)
    {
        m_pi->m_seg = new node;

        m_pi->m_seg->m_ant = n;
        n->m_seg = m_pi->m_seg;

        m_pi->m_seg->m_seg = NULL;
    }

    m_pi = m_pi->m_seg;

    m_pi->m_val = a;
}

// ######################################################################################### //

//0(1)
string easy_dial::inici() throw()
{
    //PRE: TRUE
    //POST: Inicialitza el prefix a '' i retorna el nom corresponent si existeix, si no, retorna un string buit.
    m_pref = "";
    m_indef = false;

    if (m_primer != NULL)
    {
        if (m_pi->m_p.nom().size() == 0)
        {
            node *tmp = m_pi;

            m_pi->m_ant->m_seg = NULL;

            delete tmp;
        }

        m_pi = m_primer;

        // O(1) cost mitj. Tantes iteracions com caràcters té el prefix en curs.
        borra_estructura_aux(m_primer->m_seg);

        return m_pi->m_p.nom();
    }
    else
        return "";
}

//0(1)
string easy_dial::seguent(char c) throw(error)
{
    //PRE: TRUE
    //POST: Si el prefix inical está indefinit, retorna error. Si no, afegeix al prefix el carácter c i retorna el nom corresponent. Si no hi ha cap nom, retorna un string buit.
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
    //PRE: TRUE
    //POST: Si el prefix está buit o indifenit retorna error, si no, elimina l'últim carácter del prefix. Si aquesta supressió genera un prefix indefinit, també genera error.
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
    //PRE: TRUE
    //POST: Retorna el número de teléfon corresponent al F(s, p) sent p el prefix en curs. Si no existeix F(s, p) o el prefix está indefinit, retorna error.
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
    //PRE: TRUE
    //POST: Inserta al vector tots el noms de contactes que comencin amb el prefix pref, en ordre lexicográfic creixent.
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
    //PRE: TRUE
    //POST: Emmagatzema el màxim dels phones d'un conjunt que compleixen el prefix trobat en nt prèviament.
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
    //PRE: TRUE
    //POST: A partir d'un punt de l'arbre donat com argument n cerca el prefix k.
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
    //PRE: TRUE
    //POST: A partir d'un prefix en curs busca el següent phone màxim.
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
    //PRE: TRUE.
    //POST: Inserta al vector tots el noms de contactes que comencin amb el prefix pref, en ordre lexicográfic creixent.
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
    //PRE: TRUE
    //POST: Retorna un double amb el número mitja de pulsacions necessaries per obtenir un teléfon.
    return m_freq;
}

void easy_dial::insereix(const string &k, const phone &v) throw(error)
{
    //PRE: TRUE
    //POST: Insereix la paraula K en l'arbre TST.
    m_arrel = rinsereix(m_arrel, 0, k, v);
}

//0(log K.length)
typename easy_dial::node_tst *easy_dial::rinsereix(node_tst *n, nat i, const string &k, const phone &v) throw(error)
{
    //PRE: TRUE
    //POST: Retorna l'arrel de l'abre tst on es fá l'inserció.
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

//0(1)
bool easy_dial::repetit(const string &str) const
{
    //PRE: TRUE
    //POST: Retorna un bolea indicant si el nom s'ha mostrat previament.
    node *tmp = m_pi->m_ant;

    bool visitat = false;

    while (tmp != NULL and not visitat)
    {
        if (str == tmp->m_p.nom())
            visitat = true;
        else
            tmp = tmp->m_ant;
    }

    /*
    cout << "Memory pointers: {";

    tmp = m_primer;

    while (tmp != NULL)
    {
        cout << " " << ((tmp->m_p.nom().size() == 0) ? "\"\"" : tmp->m_p.nom());
            tmp = tmp->m_seg;
    }

    cout << " } {";

    tmp = m_pi;

    while (tmp != NULL)
    {
        cout << " " << ((tmp->m_p.nom().size() == 0) ? "\"\"" : tmp->m_p.nom());
        tmp = tmp->m_ant;
    }

    cout << " }" << endl;
*/

    return visitat;
}

//0(1)
typename easy_dial::node_tst *easy_dial::max(node_tst *fesq, node_tst *fdret)
{
    //PRE: TRUE
    //POST: Dels dos nodes fills, retorna el que tingui el telefon més gran (Comparació > de la classe phone).
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
    //PRE: TRUE
    //POST: Retorna la longitud mitjana de l'arbre tst.
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
    //PRE: TRUE
    //POST: Retorna la longitud mitjana de l'arbre tst.
    return calcula_longitud(m_arrel, 0);
}

//0(n)
bool easy_dial::tst_igual(node_tst *a, node_tst *b)
{
    //PRE: TRUE
    //POST: Retorna un boolea indicant si el tst del p.i i el de l'argument són iguals.
    bool ret = true;

    if (a != NULL and b != NULL)
    {
        if (a->m_c == b->m_c)
        {
            if (a->m_c == phone::ENDPREF)
            {
                if (a->m_valor != b->m_valor)
                {
                    ret = false;
                }
            }
            else
                ret = tst_igual(a->m_fesq, b->m_fesq) and tst_igual(a->m_fcen, b->m_fcen) and tst_igual(a->m_fdret, b->m_fdret);
        }
        else
            ret = false;
    }
    else if ((a != NULL and b == NULL) or (a == NULL and b != NULL))
        ret = false;

    return ret;
}

//0(n)
bool easy_dial::aux_igual(node *a, node *b)
{

    //PRE: TRUE
    //POST: Retorna un boolea indicant si l'estructura auxiliar del p.i i la de l'argument són iguals.
    if (a != NULL and b != NULL)
        return aux_igual(a->m_seg, b->m_seg) and (a->m_val == b->m_val) and (a->m_p == b->m_p);
    else if ((a != NULL and b == NULL) or (a == NULL and b != NULL))
        return false;
    else
        return true;
}
//0(n)
bool easy_dial::es_igual(const easy_dial &D)
{
    //PRE: TRUE
    //POST: Retorna un boolea indicant si el easy_dial del p.i i el de l'argument són iguals.
    return m_pref == D.m_pref and m_indef == D.m_indef and m_freq == m_freq and tst_igual(m_arrel, D.m_arrel) and aux_igual(m_primer, D.m_primer);
}