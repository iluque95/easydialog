#include "../incl/phone.hpp"

#include "phone.hpp"

phone::phone(string nom, nat num, nat cops) : m_name(nom),
                                              m_num(num),
                                              m_cops(cops)
{
}

nat phone::numero() const throw()
{
    //PRE: True
    //POST: Retornem el numero corresponent al phone
    return m_num;
}

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

phone &phone::operator++() throw()
{
    //PRE: True
    //POST: Augmentem en 1 el numero de trucades rebudes
    ++m_cops;
    return this;
}

phone phone::operator++(int) throw()
{
    //PRE: True
    //POST: Augmentem en 1 el numero de trucades rebudes
    phone aux(*this);
    ++m_cops;
    return aux;
}

bool phone::operator==(const phone &T) const throw()
{
    //PRE: El paràmetre és un phone
    //POST: Retornem si les trucades fetes al p.i son iguals a les fetes a T
    if (m_cops == T.m_cops)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool phone::operator!=(const phone &T) const throw()
{
    //PRE: El paràmetre és un phone
    //POST: Retornem si les trucades fetes al p.i son diferents a les fetes a T
    if (m_cops != T.m_cops)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool phone::operator<(const phone &T) const throw()
{
    //PRE: El paràmetre és un phone
    //POST: Retornem si les trucades fetes al p.i son menors a les fetes a T
    if (m_cops < T.m_cops)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool phone::operator>(const phone &T) const throw()
{
    //PRE: El paràmetre és un phone
    //POST: Retornem si les trucades fetes al p.i son majors a les fetes a T
    if (m_cops < T.m_cops)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool phone::operator<=(const phone &T) const throw()
{
    //PRE: El paràmetre és un phone
    //POST: Retornem si les trucades fetes al p.i son menors o iguals a les fetes a T
    if (m_cops <= T.m_cops)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool phone::operator<(const phone &T) const throw()
{
    //PRE: El paràmetre és un phone
    //POST: Retornem si les trucades fetes al p.i son majors o iguals a les fetes a T
    if (m_cops >= T.m_cops)
    {
        return true;
    }
    else
    {
        return false;
    }
}