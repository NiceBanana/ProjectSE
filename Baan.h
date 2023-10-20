//
// Created by student on 03.03.22.
//

#ifndef INC_BAAN_H
#define INC_BAAN_H

#include <iostream>
#include <vector>
#include <map>
#include "VerkeersElement.h"

using namespace std;

class Voertuig;
class Verkeerslicht;
class VoertuigGenerator;
class Bushalte;
class Kruispunt;

class Baan {
private:
    friend class VerkeersSituatie;
    Baan* fInitCheck;
    string fNaam;
    int fLengte;
    vector<Voertuig*> fVoertuigen;
    vector<Verkeerslicht*> fVerkeerslichten;
    vector<VoertuigGenerator*> fVoertuigGeneratoren;
    vector<Bushalte*> fBushaltes;
    vector<Kruispunt*> fKruispunten;
public:
    bool properlyInitialised() const;

    /*
     * ENSURE(this->properlyInitialised(),"constructor must end in properlyInitialised state");
     */
    Baan();

    /*
     * REQUIRE(lengte>0,"Baan moet een strikt positieve lengte hebben");
     * ENSURE(this->properlyInitialised(),"constructor must end in properlyInitialised state");
     * ENSURE(fLengte>0, "Baan moet een strikt positieve lengte hebben");
     */
    Baan(const string &naam, int lengte);


    virtual ~Baan();

    /*
     * REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling getNaam");
     */
    const string &getNaam() const;

    /*
     * REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling setNaam");
     * ENSURE(fNaam==naam,"setNaam postcondition failure");
     */
    void setNaam(const string &naam);

    /*
     * REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling getLengte");
     * ENSURE(fLengte>0,"Baan moet een strikt positieve lengte hebben");
     */
    int getLengte() const;

    /*
     * REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling setLengte");
     * REQUIRE(fLengte > 0, "Baan moet een strikt positieve lengte hebben");
     * ENSURE(fLengte==lengte,"setLengte postcondition failure");
     */
    void setLengte(int lengte);


    void deleteElement(VerkeersElement*);

    /*
     * REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling getVoertuigen");
     */
    const vector<Voertuig *> &getVoertuigen() const;

    /*
     * REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling addVoertuig");
     * REQUIRE(this==voertuig->getBaan(),"Banen komen niet overeen");
     * REQUIRE(not vectorChecker(voertuig),"Voertuig zit al in de vector");
     * REQUIRE(this->getLengte()>voertuig->getPositie(),"Lengte baan moet groter zijn dan positie voertuig");
     * ENSURE(vectorChecker(voertuig),"addVoertuig postcondition failure");
     */
    void addVoertuig(Voertuig*);

    /*
     * REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling getVoorganger");
     * REQUIRE(this==voertuig->getBaan(),"Banen komen niet overeen");
     * REQUIRE(vectorChecker(voertuig),"Voertuig bevindt zich niet op de baan");
     * ENSURE(fVoertuigen[i+1]->getBaan()==this,"Banen komen niet overeen");
     * ENSURE(vectorChecker(fVoertuigen[i+1]),"Voorganger bevindt zich niet op de baan");
     */
    Voertuig* getVoorganger(Voertuig*) const;

    /*
     * REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling getVolgganger");
     * REQUIRE(this==voertuig->getBaan(),"Banen komen niet overeen");
     * REQUIRE(vectorChecker(voertuig),"Voertuig bevindt zich niet op de baan");
     * ENSURE(fVoertuigen[i-1]->getBaan()==this,"Banen komen niet overeen");
     * ENSURE(vectorChecker(fVoertuigen[i-1]),"Volgganger bevindt zich niet op de baan");
     */
    Voertuig* getVolgganger(Voertuig*) const;

    /*
     * REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling getVerkeerslichten");
     */
    const vector<Verkeerslicht *> &getVerkeerslichten() const;

    /*
     * REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling addVerkeerslicht");
     * REQUIRE(this==verkeerslicht->getBaan(),"Banen komen niet overeen");
     * REQUIRE(not vectorChecker(verkeerslicht),"Verkeerslicht zit al in de vector");
     * REQUIRE(this->getLengte()>verkeerslicht->getPositie(),"Lengte baan moet groter zijn dan positie verkeerslicht");
     * ENSURE(vectorChecker(verkeerslicht),"addVerkeerslicht postcondition failure");
     */
    void addVerkeerslicht(Verkeerslicht*);

    /*
     * REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling getVolgendeLicht");
     * REQUIRE(voertuig->getBaan()==this,"Banen komen niet overeen");
     * REQUIRE(vectorChecker(voertuig),"Voertuig bevindt zich niet op de baan");
     * ENSURE(fVerkeerslichten[i]->getBaan()==voertuig->getBaan(),"Banen komen niet overeen");
     * ENSURE(vectorChecker(fVerkeerslichten[i]),"Verkeerslicht bevindt zich niet op de baan");
     */
    Verkeerslicht* getVolgendeLicht(Voertuig*) const;

    /*
     * REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling getVoertuigGeneratoren");
     */
    const vector<VoertuigGenerator *> &getVoertuigGeneratoren() const;

    /*
     * REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling addVoertuigGenerator");
     * REQUIRE(generator->getBaan()==this,"Banen komen niet overeen");
     * REQUIRE(not vectorChecker(generator),"Generator bevindt zich al op de baan");
     * ENSURE(vectorChecker(generator),"addVoertuigGenerator postcondition failure");
     */
    void addVoertuigGenerator(VoertuigGenerator*);

    /*
     * REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling getBushaltes");
     */
    const vector<Bushalte *> &getBushaltes() const;

    /*
     * REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling addBushalte");
     * ENSURE(vectorChecker(bushalte),"addBushalte postcondition failure");
     */
    void addBushalte(Bushalte*);

    /*
     * REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling getVolgendeBushalte");
     * REQUIRE(voertuig->getBaan()==this,"Banen komen niet overeen");
     * REQUIRE(vectorChecker(voertuig),"Voertuig bevindt zich niet op de baan");
     * ENSURE(fBushaltes[i]->getBaan()==voertuig->getBaan(),"Banen komen niet overeen");
     * ENSURE(vectorChecker(fBushaltes[i]),"Bushalte bevindt zich niet op de baan");
     */
    Bushalte* getVolgendeBushalte(Voertuig*) const;

    /*
     * REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling getBushaltes");
     */
    const vector<Kruispunt*> &getKruispunten() const;

    /*
     * REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling addBushalte");
     * ENSURE(vectorChecker(kruispunt),"addBushalte postcondition failure");
     */
    void addKruispunt(Kruispunt*);

    /*
     *
     */
    Kruispunt* getVolgendeKruispunt(Voertuig*) const;
protected:
    bool vectorChecker(const Voertuig*) const;
    bool vectorChecker(const Verkeerslicht*) const;
    bool vectorChecker(const VoertuigGenerator*) const;
    bool vectorChecker(const Bushalte*) const;
    bool vectorChecker(const Kruispunt*) const;
};


#endif //RINGSTIMULATOR_BAAN_H
