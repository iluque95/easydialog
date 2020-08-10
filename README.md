# Projecte d'ESIN

Llegir en [*format PDF*](ESIN_projecte_1920q1_easydial.pdf).

- **CA**: Es recomana veure-ho en la branca de desenvolupament.
- **ES**: Se recomienda ver el proyecto en la rama de desarrollo.
- **EN**: Is recomendable see the project on develop branch.

# Normativa i Enunciat

### Tardor de 2019

Aquest document és llarg però és imprescindible que el llegiu íntegrament i amb
deteniment, àdhuc si sou repetidors, ja que es donen les instruccions i normes que heu
de seguir per a que el vostre projecte sigui avaluat positivament. El professorat de l’as-
signatura donarà per fet que tots els alumnes coneixen el contingut íntegre d’aquest
document.

## Continguts:

**1 Normativa ... 2**

**2 Enunciat del projecte ... 4**

**3 Disseny modular ... 6**

**4 La classephone ... 8**

**5 La classecall_registry ... 10**

**6 La claseeasy_dial ... 13**

**7 El mòduldialog ... 17**

**8 Errors ... 18**

**9 Documentació ... 19**

####


## 1 Normativa

1. Tal i com s’explica a la Guia Docent, per a assolir els objectius de l’assignatura es
    considera imprescindible el desenvolupament per part de l’estudiant d’un projecte
    que requereix algunes hores addicionals de treball personal, apart de les classes de
    laboratori, on es fa el desenvolupament dels altres exercicis pràctics que permeten
    familiaritzar-vos amb l’entorn de treball i el llenguatge de programació C++.
2. El projecte es realitzarà en equips de dos estudiants. Si un d’ells abandona, un
    dels integrants ho haurà de notificar amb la màxima promptitud via e-mail a
    jesteve@cs.upc.edu bcasas@cs.upc.edui, eventualment, continuar el pro-
    jecte en solitari. D’altra banda, només es permetrà la formació d’equips individu-
    als en casos excepcionals on sigui impossible reunir-se o comunicar-se amb altres
    estudiants, i s’haurà de justificar mitjançant algun tipus de document.
3. El suport que fareu servir per aquest projecte és el llenguatge de programació C++
    (específicament el compilador GNUg++-5.4.0) sobre l’entorn Linux del STIC.
    Això no és obstacle per al desenvolupament previ en PCs o similars. De fet, exis-
    teixen compiladors de C++per a tota classe de plataformes i hauria de ser senzill
    el trasllat des del vostre equip particular a l’entorn del STIC, especialment si tre-
    balleu amb GNU/Linux en el vostre PC.
    Atenció: Existeix la possibilitat de petites incompatibilitats entre alguns compila-
    dors de C++. En tot cas és imprescindible que feu almenys una comprovació final
    que el programa desenvolupat en PC o similar funciona correctament en l’entorn
    Linux del STIC (us podeu connectar remotament al servidorahto.epsevg.upc.edu).
4. El projecte serà avaluat mitjançant:
    - la seva execució en l’entorn Linux del STIC amb una sèrie dejocs de provai
    - la correcció del disseny, implementació i documentació: les decisions de dis-
       seny i la seva justificació, l’eficiència dels algorismes i estructures de dades,
       la legibilitat, robustesa i estil de programació, etc. Tota la documentació ha
       d’acompanyar el codi; no heu de lliurar cap documentació en paper.


Existeixen dos tipus de jocs de prova: públics i privats. Els jocs de prova públics
per a que podeu provar el vostre projecte estaran a la vostra disposició amb ante-
lació suficient al Campus Digital (https://atenea.upc.edu).
La nota del projecte es calcula a partir de la nota d’execució (E) i la nota de disseny
(D). La nota total és:
P= 0. 4 E+ 0. 6 D
si ambdues notes parcials (EiD) són majors que 0;P= 0si la nota de disseny és
0.
El capítol G del Manual de laboratori d’ESIN descriu, entre altres coses, les situacions
que originen una qualificació de 0 en el disseny (i per tant una qualificació de 0 del
projecte). La nota d’execució (E) és 3 punts com a mínim si s’han superat els jocs



de prova públics; en cas contrari, la nota és 0. Els jocs de prova privats poden
aportar fins a 7 punts més, en cas que s’hagin superat els jocs de prova públics.

5. La data límit del lliurament final és el 9 de gener de 2020 a les 23:55. Si un equip no
    ha lliurat el projecte llavors la nota serà 0. Al Campus Digital (https://atenea.upc.edu)
    es donaran tots els detalls sobre el procediment de lliurament del projecte.
6. No subestimeu el temps que haureu d’esmerçar a cadascun dels aspectes del pro-
    jecte: disseny, codificació, depuració d’errors, proves, documentació,...


## 2 Enunciat del projecte

Un agenda telefònica és una aplicació comuna en telèfons mòbils, smarthphones i
ordinadors. En general una persona gestiona un agenda amb una quantitat reduïda
de números de telèfon, però tot i això aquest tipus d’aplicacions ofereixen poca “in-
tel·ligència”. En els telèfons mòbils és habitual que l’única facilitat de cerca consisteixi
en prémer la lletra inicial del nom associat al número de telèfon i, un cop situats sobre
el primer dels noms que comencen amb la lletra en qüestió, hom s’hagi de desplaçar
seqüencialment per la llista fins trobar el contacte que li interessa.

En aquest projecte desenvoluparem el sistemaEasyDialque, si bé té algunes li-
mitacions, exhibeix una major “intel·ligència” i proporciona major comoditat a l’usuari.
Amb alguns esforços addicionals i una interfície d’usuari agradable podria donar origen
a una aplicació veritablement pràctica.

Una part del sistema permetria registrar números de telèfon, assignar noms a aquests
números de telèfon i comptabilitzar quantes trucades s’efectuen a cadascun dels telè-
fons.

L’altra part del sistema, la realment “innovadora”, construeix una estructura de da-
des a partir de la informació recol·lectada per l’altre subsistema. A partir d’aquí ens
permet consultar números de telèfon introduint un prefix mínim del nom. El sistema
tindrà en compte la freqüència amb que acostumem a trucar a cada número de telèfon
per fer la cerca el més ràpida i còmoda possible.

Un exemple concret ens pot ajudar a entendre com funcionaEasyDial. Per fixar
idees, suposem que l’aplicació està instal·lada en un mòbil i que la guia conté informació
dels telèfons que es poden veure a la figura 1.

```
MARIA 972261435 15 trucades
JOSEP 934578916 50 trucades
MAR 934907288 5 trucades
MIQUEL 666931459 30 trucades
MARTA 678818034 10 trucades
```
```
Figura 1: Exemple d’agenda de telèfons
```
Premem el botó de trucada. Donat que JOSEP és a qui més truquem, el sistema ens
presenta en pantalla aquest nom. Si realment volguéssim trucar-lo només hauríem de
tornar a prémer el botó de trucada (o un botó de OK) i llavors realitzaria efectivament la
trucada. Però suposem que no, que volem trucar a MARTA. Així que premem la ’M’, i
llavorsEasyDialens presenta MIQUEL, ja que és el telèfon usat més freqüentment que
comença per aquesta lletra. Novament podríem donar-li a OK si aquest fos el telèfon al
que volíem trucar, però com no és així, premem ’A’.EasyDialescriu llavors MARIA,
ja que és el telèfon que comença per ’MA’ més freqüent. Però nosaltres premerem ’R’


perquè no volem trucar a MARIA, però sí a un telèfon que comença per ’MAR’. I ara
EasyDialens proposaria MARTA, perquè és el telèfon més freqüent que comença per
’MAR’ i no ha estat rebutjat: en efecte, MARIA també comença per ’MAR’ i és més
freqüent que MARTA, però si haguéssim volgut trucar a MARIA ja no hauríem premut
la ’R’ i haguéssim confirmat la trucada a MARIA quan ens va ser proposat.

En total, ha estat suficient prémer tres lletres (’M’, ’A’, ’R’) per localitzar el telèfon
de MARTA. Per trucar a MIQUEL només necessitaríem prémer una lletra. En general
quant més freqüent sigui un telèfon més senzill serà trobar-lo a l’agenda. Només en el
pitjor dels casos hauríem d’introduir el nom complet (o un prefix que el distingeix de
tota la resta de noms) per localitzar un telèfon.

És fàcil donar-se compte que el sistema ens donarà molt bones prestacions encara
que la quantitat de números de telèfon que hagi emmagatzemats sigui molt elevada.

Resumint, el projecte comptarà, entre d’altres, amb els següents tres mòduls fona-
mentals:

1. Un mòdul permetrà emmagatzemar i gestionar informació sobre números de telè-
    fon, noms associats i freqüències de trucada a cadascun d’ells.
2. Un altre mòdul contindrà l’algorisme d’ “interacció” amb l’usuari que proposarà
    successius telèfons en funció de l’entrada que proporciona l’usuari.
3. El tercer mòdul extreu i organitza la informació proporcionada pel primer per fer
    de manera molt eficient la tasca de consulta (guiada pel segon mòdul). De fet, la
    “intel·ligència” del sistema resideix en aquest mòdul.

En les següents seccions es presenten el disseny modular que s’ha escollit per resol-
dre el problema i també la definició i descripció de les classes i mòduls que heu d’im-
plementar.


## 3 Disseny modular

```
call_registry
```
```
easy_dial
```
```
dialog
```
```
phone
```
```
driver_EasyDial
```
```
Figura 2: Disseny modular del projecte.
```
El sistemaEasyDialconsta d’un mòdul funcional anomenatdialogen el que es
defineix una funció del mateix nom que simula la interacció en la que es tecleja un nom
lletra a lletra en un mòbil i la presentació en pantalla dels noms i el número de telè-
fon final. Per tal de realitzar la seva feina, aquest mòdul usa la classeeasy_dial, la
qual recull la informació acumulada en la classecall_registryi l’emmagatzema en
una estructura de manera que les consultes siguin eficients. La classephonepermet
gestionar les dades associades a un telèfon: número, nom i comptador de trucades.

S’han omès d’aquest diagrama (figura 2) la classeerrori el mòdulutilde la biblioteca
libesinper claredat, ja que moltes classes i mòduls del diagrama usen aquests mò-
duls. La classeerrorestà documentada en elManual de laboratori d’ESIN, i el mòdulutil
està documentat on-line en el fitxeresin/util. En algunes classes d’aquest projec-
te s’usa també la classestringiiostreamde la biblioteca estàndard de C++. Aquestes
relacions d’ús i les classes en qüestió tampoc es mostren a la figura.

També tindreu a la vostra disposició, més endavant, els jocs de proves públics i el
mòduldriver_EasyDial. Aquest mòdul conté el programa principal i usa a totes les
classes que heu d’implementar, és a dir, permet invocar cada una de les operacions dels
diferents mòduls i classes,


Recordeu que no es pot utilitzar cap classe d’una biblioteca externa en les vostres
classes, exceptuant si en aquesta documentació s’indica el contrari.

En totes les classes s’han d’implementar els mètodes de construcció per còpia, as-
signació i destrucció davant la possibilitat que useu memòria dinàmica per la classe en
qüestió. Si no es fa ús de memòria dinàmica, la implementació d’aquests tres mètodes
és molt senzilla doncs n’hi haurà prou amb imitar el comportament del que serien els
corresponents mètodes d’ofici (el destructor no fa "res", i els altres fan còpies atribut per
atribut).

Així mateix us proporcionem tots els fitxers capçalera (.hpp) d’aquest disseny mo-
dular. No podeu crear els vostres propis fitxers capçalera ni modificar de cap manera els
que us donem. Tingueu present que heu de respectar escrupolosament l’especificació de
cada classe que apareix en el corresponent.hpp.

```
ATENCIÓ : És important que una cop implementat cadascuna de les classes, les
sotmeteu als vostres jocs de proves. A més, també és fonamental dissenyar amb
força detall la representació de cada classe i els seus algorismes sobre paper, i
prendre notes de tots els passos seguits abans de començar a codificar. Aquesta
informació serà vital de cara a la preparació de la documentació final.
```
En resum, en aquest projecte les tasques que heu de realitzar i l’ordre que heu de
seguir és el següent:

- Implementar la classephone.
- Implementar la classecall_registry.
- Implementar la classeeasy_dial.
- Implementar la classedialog.


## 4 La classephone

La classephoneconté les dades relatives a un telèfon: el número del telèfon, un nom
(string) associat al número, i un comptador amb el nombre de vegades que s’ha trucat
al telèfon. A aquest comptador se l’anomena indistintament comptador de trucades o
comptador de freqüència. La classe també inclou un operador de comparació>.

Decisions sobre les dades:Un número de telèfon és un natural. El nom associat a un
número és un string format per una seqüència de caràcters del codi ASCII, exceptuant
els caràctersDELETECHAR = ‘<’,ENDCHAR = ‘|’ iENDPREF = ‘\ 0 ’. Els strings no te-
nen una longitud màxima coneguda, encara que a la majoria dels casos seran “curts”.
Un string buit és admissible i indica que el número no té (encara) cap nom associat. El
comptador associat a un número de telèfon és un natural qualsevol.

Implementació:La representació d’aquesta classe es trobarà en el fitxerphone.repi
la implementació en el fitxerphone.cpp. La documentació ha de ser mínima, donada
la senzillesa de les dades i dels mètodes.

```cpp
#ifndef _PHONE_HPP
#define _PHONE_HPP

#include <string>
#include <esin/error>
#include <esin/util>

**using namespace** std;
**using** util::nat;

**class** phone{
**public** :


/* C o n s t r u e i x un t e l è f o n a p a r t i r del seu n ú m e r o ( num ) , el seu nom
( name ) i el seu c o m p t a d o r de t r u c a d e s ( c o m p t ).
Es p r o d u e i x un e r r o r si name no és un i d e n t i f i c a d o r l e g a l. */
phone(nat num=0, const string& name="", nat compt=0) throw (error);

/* Tres g r a n s. C o n s t r u c t o r per còpia , o p e r a d o r d ’ a s s i g n a c i ó
i d e s t r u c t o r. */
phone( const phone& t) throw (error);
phone& operator =( const phone& t) throw (error);
~phone() throw ();

/* R e t o r n a el n ú m e r o de t e l è f o n. */
nat numero() const throw ();

/* R e t o r n a el nom a s s o c i a t al telèfon , e v e n t u a l m e n t l ’ s t r i n g buit. */
string nom() const throw ();

/* R e t o r n a el n ú m e r o de v e g a d e s que s ’ ha t r u c a t al t e l è f o n. */
nat frequencia() const throw ();

/* O p e r a d o r de p r e i n c r e m e n t.
I n c r e m e n t a en 1 el n ú m e r o de v e g a d e s que s ’ ha t r u c a t al t e l è f o n i
r e t o r n a una r e f e r è n c i a a a q u e s t t e l è f o n. */
phone& operator ++() throw ();

/* O p e r a d o r de p o s t i n c r e m e n t.
I n c r e m e n t a en 1 el n ú m e r o de v e g a d e s que s ’ ha t r u c a t al t e l è f o n i
r e t o r n a una c ò p i a d ’ a q u e s t t e l è f o n s e n s e i n c r e m e n t a r. */
phone operator ++( int ) throw ();

/* O p e r a d o r s de c o m p a r a c i ó. L ’ o p e r a d o r > r e t o r n a cert , si i n o m é s si ,
el t e l è f o n s o b r e el que s ’ a p l i c a el m è t o d e és més f r e q ü e n t que el
t e l è f o n T , o a i g u a l f r e q ü è n c i a , el nom a s s o c i a t al t e l è f o n és
m a j o r en o r d r e l e x i c o g r à f i c que el nom a s s o c i a t a T.
La r e s t a d ’ o p e r a d o r s es d e f i n e i x e n c o n s i s t e n t m e n t r e s p e c t e a >. */
bool operator ==( const phone& t) const throw ();
bool operator !=( const phone& t) const throw ();
bool operator <( const phone& t) const throw ();
bool operator >( const phone& t) const throw ();
bool operator <=( const phone& t) const throw ();
bool operator >=( const phone& t) const throw ();

/* C a r à c t e r s e s p e c i a l s no p e r m e s o s en un nom de t e l è f o n. */
static const char DELETECHAR = ’<’;
static const char ENDCHAR = ’|’;
static const char ENDPREF = ’\0’;

/* G e s t i ó d ’ e r r o r s. */
static const int ErrNomIncorrecte = 11;

**private** :
#include "phone.rep"
};
#endif
```


## 5 La classecall_registry

La classecall_registryconté les dades relatives a un conjunt de telèfons. Recor-
dem que un telèfon consta de número, nom associat (que eventualment pot ser l’string
buit) i un comptador de trucades. La classe ofereix operacions per assignar un nom a un
telèfon, registrar que s’ha produït una trucada, consultes, etc.

L’operacióassigna_nompot ser utilitzada per assignar un nom a un telèfon que no
tenia un nom associat, modificar el nom associat a un telèfon donat i eliminar el nom
associat a un telèfon (assignant l’string buit).

És important destacar que no és un problema que en un moment donat dos o més
números tinguin el mateix nom i per aixòassigna_nomno fa comprovacions al res-
pecte.

La classe també inclou una operació de bolcat (dump), la qual copia totes les entrades
que tenen un nom associat no buit, en un ordre qualsevol, en unvectordephones.

Decisions sobre les dades: Un objecte de la classecall_registryconté un conjunt
de telèfons de mida no acotada, amb la limitació que tots els números de telèfon han de
ser diferents.

Implementació:La representació d’aquesta classe es trobarà en el fitxercall_registry.rep
i la implementació en el fitxercall_registry.cpp. Només es pot usar la classe
vectorde la biblioteca estàndard de C++ en el mètodedump.

Les operacions d’aquesta classe han de ser totes eficients en el cas pitjor o mitjà. En
particular, el constructor per còpia, l’assignació i el destructor han de tenir cost lineal.
Tota la resta d’operacions, exceptedump, han de tenir cost logarítmic o inferior.

```cpp
#ifndef _CALL_REGISTRY_HPP
#define _CALL_REGISTRY_HPP

#include "phone.hpp"
#include <esin/error>
#include <esin/util>
#include <string>
#include <vector>

**using namespace** std;
**using** util::nat;

**class** call_registry {
**public** :


/* C o n s t r u e i x un c a l l _ r e g i s t r y buit. */
call_registry() throw (error);


/* C o n s t r u c t o r per còpia , o p e r a d o r d ’ a s s i g n a c i ó i d e s t r u c t o r. */
call_registry( **const** call_registry& cr) **throw** (error);
call_registry& **operator** =( **const** call_registry& cr) **throw** (error);
~call_registry() **throw** ();

/* R e g i s t r a que s ’ ha r e a l i t z a t una t r u c a d a al n ú m e r o donat ,
i n c r e m e n t a n t en 1 el c o m p t a d o r de t r u c a d e s a s s o c i a t. Si el n ú m e r o
no e s t a v a p r è v i a m e n t en el c a l l _ r e g i s t r y a f e g e i x una nova e n t r a d a
amb el n ú m e r o de t e l è f o n donat , l ’ s t r i n g buit com a nom i el
c o m p t a d o r a 1. */
**void** registra_trucada(nat num) **throw** (error);

/* A s s i g n a el nom i n d i c a t al n ú m e r o d o n a t.
Si el n ú m e r o no e s t a v a p r è v i a m e n t en el c a l l _ r e g i s t r y , s ’ a f e g e i x
una nova e n t r a d a amb el n ú m e r o i nom donats , i el c o m p t a d o r
de t r u c a d e s a 0.
Si el n ú m e r o e x i s t i a p r è v i a m e n t , se li a s s i g n a el nom d o n a t. */
**void** assigna_nom(nat num, **const** string& name) **throw** (error);

/* E l i m i n a l ’ e n t r a d a c o r r e s p o n e n t al t e l è f o n el n ú m e r o de la qual
es dóna. Es p r o d u e i x un e r r o r si el n ú m e r o no e s t a v a p r e s e n t. */
**void** elimina(nat num) **throw** (error);

/* R e t o r n a cert si i n o m é s si el c a l l _ r e g i s t r y c o n t é un
t e l è f o n amb el n ú m e r o d o n a t. */
**bool** conte(nat num) **const throw** ();

/* R e t o r n a el nom a s s o c i a t al n ú m e r o de t e l è f o n que s ’ i n d i c a.
A q u e s t nom pot ser l ’ s t r i n g buit si el n ú m e r o de t e l è f o n no
té un nom a s s o c i a t. Es p r o d u e i x un e r r o r si el n ú m e r o no està en
el c a l l _ r e g i s t r y. */
string nom(nat num) **const throw** (error);

/* R e t o r n a el c o m p t a d o r de t r u c a d e s a s s o c i a t al n ú m e r o de t e l è f o n
i n d i c a t. A q u e s t n ú m e r o pot ser 0 si no s ’ ha e f e c t u a t cap t r u c a d a a
a q u e s t n ú m e r o. Es p r o d u e i x un e r r o r si el n ú m e r o no està en el
c a l l _ r e g i s t r y. */
nat num_trucades(nat num) **const throw** (error);

/* R e t o r n a cert si i n o m é s si el c a l l _ r e g i s t r y està buit. */
**bool** es_buit() **const throw** ();

/* R e t o r n a q u a n t s n ú m e r o s de t e l è f o n hi ha en el c a l l _ r e g i s t r y. */
nat num_entrades() **const throw** ();


/* Fa un b o l c a t de t o t e s les e n t r a d e s que t e n e n a s s o c i a t un
nom no nul s o b r e un v e c t o r de p h o n e.
C o m p r o v a que tots els noms dels t e l è f o n s s i g u i n d i f e r e n t s ;



es p r o d u e i x un e r r o r en cas c o n t r a r i. */
void dump(vector<phone>& V) const throw (error);

/* G e s t i ó d ’ e r r o r s. */
static const int ErrNumeroInexistent = 21;
static const int ErrNomRepetit = 22;

**private** :
#include "call_registry.rep"
};
#endif
```


## 6 La claseeasy_dial

La classeeasy_dialconté una estructura de dades que permet fer cerques usant
prefixos dels noms associats als números de telèfon i usant la informació sobre la fre-
qüència de trucades a cada un d’aquests números.

Un objecte de la classeeasy_diales construeix a partir de les dades registrades
en un objecte de la classecall_registry. És important destacar que uneasy_dial
és una estructura estàtica, en el sentit que la informació sobre els telèfons no es pot
modificar una cop construïda. Per tant, sobre un objecte de la classeeasy_diales
poden fer consultes però no insercions ni esborrats.

Associat a cada objecte de la classeeasy_dialtenim la noció deprefix en curs.
Aquest prefix es construeix lletra a lletra i seqüencialment. L’operacióseguentafegeix
una lletra al prefix en curs pel final, i l’operacióanterioresborra l’última lletra del
prefix en curs. Per indicar fi de paraula s’usa la constant de classephone::ENDPREF.
Recordeu que aquesta constant és el caràcter ‘\ 0 ’ el codi ASCII de la qual és 0 i per tant
és el menor dels caràcters. Resulta convenient imaginar que tots els noms que hi ha en
uneasy_dialestan marcats al final ambphone::ENDPREF. D’aquesta manera, cap
nom és prefix d’un altre i per això quanphone::ENDPREFes dóna com argument de
l’operacióseguentestem indicant que el prefix en curs ja és un nom exacte.

Per poder descriure amb tota precisió el comportament de les diverses operacions
d’aquesta classe ens calen les següents definicions:

1. Donat un conjunt de telèfonsS = {t 1 , t 2 ,... , tn}i una cadenap(eventualment
    buida)
       Pref(S, p) ={t∈S|pés un prefix del nom det}.

```
Per exemple, pel conjunt de telèfonsSque s’usa en la figura 1,
```
- Pref(S,“MA”) ={t 1 , t 3 , t 5 }, és a dir, els telèfons de MARIA, MAR i MARTA,
    respectivament.
- Pref(S,“MAR”) ={t 1 , t 3 , t 5 }.
- Pref(S,“MAR\0”) ={t 3 }.
2. Donat un conjunt de telèfonsSi una cadenap(eventualment buida),

```
F(S, p) = max
```
```


t | t∈
```
```

Pref(S, p)\
⋃
q⊂p
```
```
F(S, q)
```
```


```
```


,
```

a onq⊂psignifica queqés prefix dep(però no igual ap). El màxim del conjunt
de telèfons es defineix a partir del criteri d’ordenació donat en la classephone; és
a dir, per freqüència, i en cas d’empat, per nom. Si el conjunt de telèfons sobre el
que s’aplicamaxés buit llavors direm queF(S, p)no existeix.

En paraules,F(S, p)és el màxim telèfon el nom de qual comença pel prefixp, però
no és el màxim telèfon el nom del qual comença pel prefixq, per cap prefix estricte
qdep.

Decisions sobre les dades:La classeeasy_dialés un conjunt de mida no acotada amb
la propietat que tots els noms i tots els números de telèfon són diferents entre sí. A més
no hi ha cap nom buit. Però l’string buit es retorna per indicar que no existeixen telèfons
amb un prefix donat en l’operacióseguent.

Implementació:La representació d’aquesta classe es trobarà en el fitxereasy_dial.rep
i la implementació en el fitxereasy_dial.cpp. Òbviament s’utilitza la classestring.

Les operacions d’aquesta classe han de ser totes eficients en el cas pitjor o mitjà, te-
nint en compte que l’alfabet sobre el qual es construeixen els strings té un número cons-
tant de lletres (unes quantes desenes). En particular, és obligatori que el constructor per
còpia, l’assignació i el destructor tinguin cost lineal respecte el número de noms emma-
gatzemats en eleasy_dial. És obligatori també que les operacionsinici,seguent
ianteriortinguin cost constant respecte el número de noms. Finalment, l’operació
consultoranum_telftambé ha de tenir cost constant.

En la implementació d’aquesta classe s’ha de tenir en compte (com a totes les classes
i mòduls, però aquí especialment) el cost en espai, ja que és fàcil dissenyar estructures
que consumeixin molta més memòria de la necessària.

**N.B. Es valorarà especialment que es compleixin els requeriments sobre el cost
temporal de les operacions d’aquesta classe**.

```cpp

#ifndef _EASY_DIAL_HPP
#define _EASY_DIAL_HPP

#include "call_registry.hpp"
#include <esin/error>
#include <esin/util>
#include <string>

**using namespace** std;
**using** util::nat;

**class** easy_dial {
**public** :
/* C o n s t r u e i x un e a s y _ d i a l a p a r t i r de la
i n f o r m a c i ó c o n t i n g u d a en el c a l l _ r e g i s t r y d o n a t. El
p r e f i x en curs q u e d a i n d e f i n i t. */
easy_dial( **const** call_registry& R) **throw** (error);


/* Tres g r a n s. C o n s t r u c t o r per còpia , o p e r a d o r d ’ a s s i g n a c i ó
i d e s t r u c t o r. */
easy_dial( const easy_dial& D) throw (error);


easy_dial& **operator** =( **const** easy_dial& D) **throw** (error);
~easy_dial() **throw** ();

/* I n i c i a l i t z a el p r e f i x en curs a buit. R e t o r n a el nom de F ( S , ’ ’);
si F ( S , ’ ’) no e x i s t e i x l l a v o r s r e t o r n a l ’ s t r i n g buit. */
string inici() **throw** ();

/* R e t o r n a el nom de F ( S , p ’) on p ’ és el p r e f i x r e s u l t a n t d ’ a f e g i r
el c a r à c t e r c al f i n a l del p r e f i x en curs p i
fa que el nou p r e f i x en curs s i g u i p ’.
Si F ( S , p ) e x i s t e i x però F ( S , p ’) no e x i s t e i x l l a v o r s r e t o r n a
l ’ s t r i n g buit.
Si no e x i s t e i x F ( S , p ) ( i per tant t a m p o c pot e x i s t i r F ( S , p ’))
l l a v o r s es p r o d u e i x un e r r o r i el p r e f i x en curs q u e d a i n d e f i n i t.
N a t u r a l m e n t , es p r o d u e i x un e r r o r si el p r e f i x en curs i n i c i a l p
fos i n d e f i n i t. */
string seguent( **char** c) **throw** (error);

/* E l i m i n a l ’ ú l t i m c a r à c t e r del p r e f i x en curs p = p ’ · a
( a és el c a r à c t e r e l i m i n a t ). R e t o r n a el nom F ( S , p ’)
i fa que el nou p r e f i x en curs s i g u i p ’.
Es p r o d u e i x un e r r o r si p fos b u i d a i si es fa que el p r e f i x en curs
q u e d i i n d e f i n i t. Ò b v i a m e n t , t a m b é es p r o d u e i x un e r r o r
si p fos i n d e f i n i t. */
string anterior() **throw** (error);

/* R e t o r n a el n ú m e r o de t e l è f o n de F ( S , p ) , sent p
el p r e f i x en curs. Es p r o d u e i x un e r r o r si p és i n d e f i n i t o si
no e x i s t e i x F ( S , p ). */
nat num_telf() **const throw** (error);

/* R e t o r n a en el v e c t o r r e s u l t tots els noms dels c o n t a c t e s de
t e l è f o n que c o m e n c e n amb el p r e f i x pref , en o r d r e l e x i c o g r à f i c
c r e i x e n t. */
**void** comencen( **const** string& pref,
vector<string>& result) **const throw** (error);

/* R e t o r n a el n ú m e r o m i t j à de p u l s a c i o n s n e c e s s à r i e s para o b t e n i r un
t e l è f o n. F o r m a l m e n t , si X és el c o n j u n t de noms e m m a g a t z e m a t s en
el e a s y _ d i a l i t ( s ) és el n ú m e r o de p u l s a c i o n s m í n i m e s
n e c e s s à r i e s (= n ú m e r o de c r i d e s a l ’ o p e r a c i ó s e g u e n t ) per
o b t e n i r el t e l è f o n el nom del qual és s. La f u n c i ó r e t o r n a la suma
Pr ( s ) · t ( s )
per tots els t e l è f o n s s del c o n j u n t X , sent Pr ( s ) la p r o b a b i l i t a t de
t e l e f o n a r a s. La p r o b a b i l i t a t s ’ obté d i v i d i n t la f r e q ü è n c i a de s per
la suma de t o t e s les f r e q ü è n c i e s. */
**double** longitud_mitjana() **const throw** ();



/* G e s t i ó d ’ e r r o r s. */
static const int ErrPrefixIndef = 31;
static const int ErrNoExisteixTelefon = 32;
static const int ErrNoHiHaAnterior = 33;

**private** :
#include "easy_dial.rep"
};
#endif
```


## 7 El mòdul dialog

Conté la funciódialogque simula la interacció entre el sistemaEasyDiali un usu-
ari. L’operació rep un objecte de la classeeasy_diali un string que és la seqüència de
pulsacions que efectua l’usuari. A més dels caràcters convencionals l’string pot contenir
aparicions del caràcterphone::DELETECHAR=’<’ que representa a la tecla d’esborrat
del caràcter premut prèviament, i aparicions del caràcterphone::ENDCHAR=’|’ que l’u-
suari utilitza per indicar que el prefix entrat fins el moment és un nom complet.

L’operació retorna un vector d’strings amb els successius noms que el sistema pre-
sentaria per pantalla i el número de telèfon corresponent a l’últim nom o un 0 si el nom
no està.

Implementació:La implementació de l’operaciódialogi les funcions auxiliars que
es considerin oportunes, es trobaran exclusivament en el fitxerdialog.cpp. No es
pot usar cap classe de la STL (Standard Template Library) per la implementació d’aquest
mòdul, llevat de la classevector.

```cpp

#ifndef _DIALOG_HPP
#define _DIALOG_HPP

#include "easy_dial.hpp"
#include <esin/error>
#include <esin/util>
#include <string>
#include <vector>

**using namespace** std;
**using** util::nat;

**namespace** dialog {


/* R e t o r n a en el v e c t o r a n s w e r s els r e s u l t a t s o b t i n g u t s al p r o c e s s a r
els s u c c e s s i u s c a r à c t e r s de l ’ s t r i n g input , i en n u m t e l f r e t o r n a
el n ú m e r o de t e l è f o n c o r r e s p o n e n t a l ’ ú l t i m nom o b t i n g u t o un 0 si
no e x i s t e i x a q u e s t nom de t e l è f o n. Si d u r a n t el p r o c e s s a m e n t de la
s e q ü è n c i a de t e c l e s r e p r e s e n t a d a en i n p u t es p r o d u í s un e r r o r
l l a v o r s a a n s w e r s es r e g i s t r a el m i s s a t g e d ’ e r r o r a s s o c i a t a
l ’ excepció , n u m t e l f és un 0 i f i n a l i t z a el p r o c é s. */
void dialog(easy_dial& easy, const string& input,
vector<string>& answers, nat& numtelf) throw ();

};
#endif

```


## 8 Errors


Aquest fitxer conté els missatges d’error usats en la gestió d’errors.

```
11 phone Nom incorrecte.

21 call_registry Numero inexistent.
22 call_registry Nom repetit.

31 easy_dial Prefix en curs indefinit.
32 easy_dial No hi ha telefons amb el prefix en curs.
33 easy_dial No es pot eliminar caracter en el prefix en curs.
```

## 9 Documentació

Els fitxers lliurats han d’estar degudament documentats. És molt important des-
criure amb detall i precisió la representació escollida en el fitxer.rep, justificant les
eleccions fetes, així com les operacions de cada classe. És especialment important ex-
plicar amb detall les representacions i els motius de la seva elecció enfront a possibles
alternatives, i els algorismes utilitzats.

El cost en temps i en espai és freqüentment el criteri determinant en l’elecció, per
la qual cosa s’hauran de detallar aquests costs en la justificació (sempre que això sigui
possible) per a cada alternativa considerada i per a l’opció finalment escollida. A més
caldrà detallar en el fitxer.cppel cost de cada mètode públic i privat.


En definitiva heu de:

- comentar adequadament el codi, evitant comentaris inútils i superflus
- indicar, en la mesura que sigui possible, el cost dels mètodes de les classes (tant
    públics com privats)
- descriure amb detall i precisió la representació escollida i justifiqueu l’elecció res-
    pecte d’altres.

Un cop enviats els fitxers per via electrònica, aquests seran impresos per a la seva
avaluació. No haureu d’imprimir-los vosaltres. No haureu de lliurar cap altra docu-
mentació. Per tal d’unificar l’aspecte visual del codi fem servir una eina deprettyprin-
tinganomenadaastyle. Podeu comprovar els resultats que produeix elprettyprinter
mitjançant la comanda

```
% astyle --style=kr -s2 < fitxer.cpp > fitxer.formatejat
```
```
i a continuació podeu convertir-lo en un PDF per visualitzar-lo o imprimir-lo
```
```
% a2ps fitxer.formatejat -o - | ps2pdf - fitxer.pdf
```
