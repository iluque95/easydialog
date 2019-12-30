#include "phone.hpp"

class phone{
public:

    nat phone::numero() const throw(){
        //PRE: Rebem un phone en el p.i
        //POST: Retornem el numero corresponent al phone
        return num;
    }

    string phone::nom() const throw(){
        //PRE: Rebem un phone en el p.i
        //POST: Retornem el nom corresponent al phone
        return nom;
    }

    nat phone::frequencia() const throw(){
        //PRE: Rebem un phone en el p.i
        //POST: Retornem el numero de trucades fetes al phone
        return compt;
    }

    phone& phone::operator++() throw(){
        //PRE:
        //POST: Augmentem en 1 el numero de trucades rebudes
        ++compt;
        return this;
    }

    phone phone::operator++(int) throw(){
        //PRE:
        //POST: Augmentem en 1 el numero de trucades rebudes
        phone aux(*this);
        ++compt;
        return aux;
    }

    bool phone::operator==(const phone& T) const throw(){
        //PRE: Rebem un phone per p.i i un altre T
        //POST: Retornem si les trucades fetes al p.i son iguals a les fetes a T
        if ( compt == T.compt ) { 
            return true;
        } else {
            return false;
        }
    }

    bool phone::operator!=(const phone& T) const throw(){
        //PRE: Rebem un phone per p.i i un altre T
        //POST: Retornem si les trucades fetes al p.i son diferents a les fetes a T
        if ( compt != T.compt ) { 
            return true;
        } else {
            return false;
        }
    }

    bool phone::operator<(const phone& T) const throw(){
        //PRE: Rebem un phone per p.i i un altre T
        //POST: Retornem si les trucades fetes al p.i son menors a les fetes a T
        if ( compt < T.compt ) { 
            return true;
        } else {
            return false;
        }
    }

    bool phone::operator>(const phone& T) const throw(){
        //PRE: Rebem un phone per p.i i un altre T
        //POST: Retornem si les trucades fetes al p.i son majors a les fetes a T
        if ( compt < T.compt ) { 
            return true;
        } else {
            return false;
        }
    }

    bool phone::operator<=(const phone& T) const throw(){
        //PRE: Rebem un phone per p.i i un altre T
        //POST: Retornem si les trucades fetes al p.i son menors o iguals a les fetes a T
        if ( compt <= T.compt ) { 
            return true;
        } else {
            return false;
        }
    }

    bool phone::operator<(const phone& T) const throw(){
        //PRE: Rebem un phone per p.i i un altre T
        //POST: Retornem si les trucades fetes al p.i son majors o iguuals a les fetes a T
        if ( compt >= T.compt ) { 
            return true;
        } else {
            return false;
        }
    }


}







