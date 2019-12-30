#include "../incl/phone.hpp"

#include "phone.hpp"

// θ(name.lenght)
phone::phone(nat num, const string &name, nat compt) throw(error) :

                                                                    m_nom(name),
                                                                    m_num(num),
                                                                    m_cops(compt)
{
    //PRE: El string nom no pot contenir cap dels carácters especials.
    //POST: Crea un phone.
    for (nat i = 0U; i < name.size(); ++i)
    {
        if (name[i] == DELETECHAR or name[i] == ENDCHAR or name[i] == ENDPREF)
            throw error(ErrNomIncorrecte);
    }
}

// θ(1)
phone::phone(const phone &T) throw(error)
{
    //PRE: TRUE
    //POST: p.i. és una copia exacte de T
    m_nom = T.m_nom;
    m_num = T.m_num;
    m_cops = T.m_cops;
}

// θ(1)
phone &phone::operator=(const phone &T) throw(error)
{
    //PRE: TRUE
    //POST: Asigna al p.i. els valors de T
    if (this != &T)
    {
        m_nom = T.m_nom;
        m_num = T.m_num;
        m_cops = T.m_cops;
    }

    return *this;
}

// θ(1)
phone::~phone() throw()
{
    //PRE: TRUE
    //POST: p.i. eliminat de memoria.
}

// θ(1)
nat phone::numero() const throw()
{
    //PRE: True
    //POST: Retornem el numero corresponent al phone
    return m_num;
}

// θ(1)
string phone::nom() const throw()
{
    //PRE: True
    //POST: Retornem el nom corresponent al phone
    return m_nom;
}

nat phone::frequencia() const throw()
{
    //PRE: True
    //POST: Retornem el numero de trucades fetes al phone
    return m_cops;
}

// θ(1)
phone &phone::operator++() throw()
{
    //PRE: True
    //POST: Augmentem en 1 el numero de trucades rebudes
    ++m_cops;
    return *this;
}

// θ(1)
phone phone::operator++(int) throw()
{
    //PRE: True
    //POST: Augmentem en 1 el numero de trucades rebudes
    phone aux(*this);
    ++m_cops;
    return aux;
}

// θ(name.lenght)
bool phone::operator==(const phone &T) const throw()
{
    //PRE: El paràmetre és un phone
    //POST: Retornem si les trucades fetes al p.i son iguals a les fetes a T
    if ((m_nom == T.m_nom) and (m_cops == T.m_cops))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// θ(name.lenght)
bool phone::operator!=(const phone &T) const throw()
{
    //PRE: El paràmetre és un phone
    //POST: Retornem si les trucades fetes al p.i son diferents a les fetes a T
    return not(*this == T);
}

// θ(name.lenght)
bool phone::operator<(const phone &T) const throw()
{
    //PRE: El paràmetre és un phone
    //POST: Retornem si les trucades fetes al p.i son menors a les fetes a T
    if ((m_cops < T.m_cops) or (m_cops == T.m_cops and m_nom < T.m_nom))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// θ(name.lenght)
bool phone::operator>(const phone &T) const throw()
{
    //PRE: El paràmetre és un phone
    //POST: Retornem si les trucades fetes al p.i son menors a les fetes a T
    if ((m_cops > T.m_cops) or (m_cops == T.m_cops and m_nom > T.m_nom))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// θ(name.lenght)
bool phone::operator<=(const phone &T) const throw()
{
    //PRE: El paràmetre és un phone
    //POST: Retornem si les trucades fetes al p.i son menors o iguals a les fetes a T
    if ((*this < T) or (*this == T))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// θ(name.lenght)
bool phone::operator>=(const phone &T) const throw()
{
    //PRE: El paràmetre és un phone
    //POST: Retornem si les trucades fetes al p.i son majors o iguals a les fetes a T
    if ((*this > T) or (*this == T))
    {
        return true;
    }
    else
    {
        return false;
    }
}