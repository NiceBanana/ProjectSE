//
// Created by student on 03.03.22.
//

#ifndef INC_VERKEERSLICHT_H
#define INC_VERKEERSLICHT_H

#include "VerkeersElement.h"

enum kleur {
    groen,
    rood,
    oranje
};

class Voertuig;
class Kruispunt;
class Verkeerslicht: public VerkeersElement {
private:
    int fCyclus;
    double fCurTijd;
    kleur fKleur;
    Kruispunt* fKruispunt;
    bool fMaster;
protected:
    void switchKleur();
public:
    bool properlyInitialised() const;

    /*
     * ENSURE(properlyInitialised(),"constructor must end in properlyInitialised state");
     */
    Verkeerslicht();


    Verkeerslicht(Baan *baan, double positie);

    /*
     * REQUIRE(fCyclus>=0,"Cyclus moet strikt positief zijn");
     */
    Verkeerslicht(Baan *baan, double positie, int cyclus);


    virtual ~Verkeerslicht();


    virtual void setBaan(Baan *baan);

    /*
     * REQUIRE(this->properlyInitialised(),"Verkeerslicht wasn't initialised when calling getCyclus");
     * ENSURE(fCyclus>0,"Cyclus moet strikt positief zijn");
     */
    int getCyclus() const;

    /*
     * REQUIRE(this->properlyInitialised(),"Verkeerslicht wasn't initialised when calling setCyclus");
     * REQUIRE(cyclus>0,"Cyclus moet strikt positief zijn");
     * ENSURE(fCyclus==cyclus,"setCyclus postcondition failure");
     */
    void setCyclus(int cyclus);

    /*
     * REQUIRE(this->properlyInitialised(),"Verkeerslicht wasn't initialised when calling update");
     * REQUIRE(newTijd>0,"Tijd moet strikt positief zijn");
     * ENSURE(delta>0,"Tijdsverschil moet strikt positief zijn");
     * ENSURE(fCurTijd==0,"Time hasn't reset after switching colours");
     */
    void update(double deltaTime);

    /*
     * REQUIRE(this->properlyInitialised(),"Verkeerslicht wasn't initialised when calling getKleur");
     */
    kleur getKleur() const;

    /*
     * REQUIRE(this->properlyInitialised(),"Verkeerslicht wasn't initialised when calling getKleur");
     */
    Kruispunt *getKruispunt() const;

    /*
     * REQUIRE(this->properlyInitialised(),"Verkeerslicht wasn't initialised when calling getKleur");
     * REQUIRE(kruispunt->getBanen().first==fBaan or kruispunt->getBanen().second==fBaan,"Banen komen niet overeen");
     * ENSURE(fKruispunt==kruispunt,"setKruispunt postcondition failure");
     */
    void setKruispunt(Kruispunt *kruispunt);

    /*
     * REQUIRE(this->properlyInitialised(),"Verkeerslicht wasn't initialised when calling isMaster");
     */
    bool isMaster() const;

    /*
     * REQUIRE(this->properlyInitialised(),"Verkeerslicht wasn't initialised when calling setMaster");
     * ENSURE(fMaster==master,"setMaster postcondition failure");
     */
    void setMaster(bool master);

    /*
     * REQUIRE(Kleur==rood or Kleur==groen or Kleur==oranje,"Licht moet een geldige kleur hebben");
     * ENSURE(fKleur==Kleur,"setKleur postcondition failure");
     */
    void setKleur(kleur fKleur);

    /*
     * REQUIRE(properlyInitialised(),"Verkeerslicht wasn't initialised when calling getClosestVehicle");
     */
    Voertuig* getClosestVehicle();
};


#endif //RINGSTIMULATOR_VERKEERSLICHT_H
