//
// Created by student on 03.03.22.
//

#include "Verkeerslicht.h"
#include "VerkeersSituatie.h"
#include "Baan.h"
#include "Kruispunt.h"
#include "Voertuig.h"
#include "lib/DesignByContract.h"

#include <cmath>

bool Verkeerslicht::properlyInitialised() const {
    return fInitCheck==this;
}

Verkeerslicht::Verkeerslicht() : fCurTijd(0) {
    fType = VERKEERSLICHT;
    fKleur = rood;
    fKruispunt = NULL;
    fMaster= true;
    fInitCheck=this;
    ENSURE(properlyInitialised(),"constructor must end in properlyInitialised state");
}

Verkeerslicht::Verkeerslicht(Baan *baan, double positie) : VerkeersElement(baan, positie), fCurTijd(0) {
    fType = VERKEERSLICHT;
    baan->addVerkeerslicht(this);
    fKleur = rood;
    fKruispunt = NULL;
    fMaster= true;
}

Verkeerslicht::Verkeerslicht(Baan *baan, double positie, int cyclus) : VerkeersElement(baan, positie),
                                                                          fCyclus(cyclus), fCurTijd(0) {
    REQUIRE(fCyclus>=0,"Cyclus moet strikt positief zijn");
    fType = VERKEERSLICHT;
    baan->addVerkeerslicht(this);
    fKleur = rood;
    fKruispunt = NULL;
    fMaster= true;
}

Verkeerslicht::~Verkeerslicht() {}

void Verkeerslicht::setBaan(Baan *baan) {
    VerkeersElement::setBaan(baan);
    baan->addVerkeerslicht(this);
}

int Verkeerslicht::getCyclus() const {
    REQUIRE(this->properlyInitialised(),"Verkeerslicht wasn't initialised when calling getCyclus");
    ENSURE(fCyclus>0,"Cyclus moet strikt positief zijn");
    return fCyclus;
}

void Verkeerslicht::setCyclus(int cyclus) {
    REQUIRE(this->properlyInitialised(),"Verkeerslicht wasn't initialised when calling setCyclus");
    REQUIRE(cyclus>0,"Cyclus moet strikt positief zijn");
    Verkeerslicht::fCyclus = cyclus;
    ENSURE(fCyclus==cyclus,"setCyclus postcondition failure");
}

void Verkeerslicht::update(double newTijd) {
    REQUIRE(this->properlyInitialised(),"Verkeerslicht wasn't initialised when calling update");
    REQUIRE(newTijd>0,"Tijd moet strikt positief zijn");
    double orangeTime=fCyclus/10.00;
    if(fKruispunt != NULL) {
        double delta = newTijd - fCurTijd;
        if(fKleur==oranje){
            if(delta>orangeTime){
                switchKleur();
                fCurTijd = newTijd - std::fmod(delta, fCyclus);
                delta = newTijd - fCurTijd;
            }
            return;
        }
        else if (delta > fCyclus) {
            switchKleur();
            fCurTijd = newTijd - std::fmod(delta, fCyclus);
            delta = newTijd - fCurTijd;
        }
        ENSURE(delta>0,"Tijdsverschil moet strikt positief zijn");
    } else {
        if(isMaster()){
            if(fCurTijd>10 and fCurTijd<60){
                Verkeerslicht* anderLicht=fKruispunt->getOtherVerkeerslicht(this);
                Voertuig* vehicle1= this->getClosestVehicle();
                Voertuig* vehicle2= anderLicht->getClosestVehicle();
                double distance1=fPositie-vehicle1->getPositie();
                double distance2=anderLicht->fPositie-vehicle2->getPositie();
                if(distance1<distance2){
                    if(fKleur==rood) {
                        this->switchKleur();
                        fCurTijd=0;
                    }
                    else if(fKleur==oranje){
                        if(fCurTijd>orangeTime){
                            this->switchKleur();
                            fCurTijd=0;
                        }
                    }
                } else {
                    if(anderLicht->fKleur==rood){
                        this->switchKleur();
                        fCurTijd=0;
                    }
                    else if(anderLicht->fKleur==oranje){
                        this->switchKleur();
                        fCurTijd=0;
                    }

                }
            }
            else if(fCurTijd>60){
                this->switchKleur();
                fCurTijd=0;
            } else {
                return;
            }
        }
        ENSURE(fCurTijd==0,"Time hasn't reset after switching colours");
    }
}

void Verkeerslicht::setKleur(kleur Kleur) {
    REQUIRE(Kleur==rood or Kleur==groen or Kleur==oranje,"Licht moet een geldige kleur hebben");
    Verkeerslicht::fKleur = Kleur;
    fCurTijd=0;
    if(fKruispunt!=NULL){
        Verkeerslicht* anderLicht=fKruispunt->getOtherVerkeerslicht(this);
        if(fKleur==groen){
            anderLicht->fKleur=rood;
            anderLicht->fCurTijd=0;
            ENSURE(anderLicht->fKleur==rood,"setKleur postcondition failure");
        }
        else if(fKleur==rood){
            anderLicht->fKleur=groen;
            anderLicht->fCurTijd=0;
            ENSURE(anderLicht->fKleur==groen,"setKleur poscondition failure");
        }
        else{
            anderLicht->fKleur=rood;
            anderLicht->fCurTijd=0;
            ENSURE(anderLicht->fKleur==rood,"setKleur postcondition failure");
        }
        ENSURE(anderLicht->fCurTijd==0,"Tijd van ander verkeerslicht is niet gereset");
    }
    ENSURE(fKleur==Kleur,"setKleur postcondition failure");
    ENSURE(fCurTijd==0,"Tijd van verkeerslicht is niet gereset");

}

kleur Verkeerslicht::getKleur() const {
    REQUIRE(this->properlyInitialised(),"Verkeerslicht wasn't initialised when calling getKleur");
    return fKleur;
}

Kruispunt *Verkeerslicht::getKruispunt() const {
    REQUIRE(this->properlyInitialised(),"Verkeerslicht wasn't initialised when calling getKleur");
    return fKruispunt;
}

void Verkeerslicht::setKruispunt(Kruispunt *kruispunt) {
    REQUIRE(this->properlyInitialised(),"Verkeerslicht wasn't initialised when calling getKleur");
    REQUIRE(kruispunt->getBanen().first==fBaan or kruispunt->getBanen().second==fBaan,"Banen komen niet overeen");
    Verkeerslicht::fKruispunt = kruispunt;
    ENSURE(fKruispunt==kruispunt,"setKruispunt postcondition failure");
}

bool Verkeerslicht::isMaster() const {
    REQUIRE(this->properlyInitialised(),"Verkeerslicht wasn't initialised when calling isMaster");
    return fMaster;
}

void Verkeerslicht::setMaster(bool master) {
    REQUIRE(this->properlyInitialised(),"Verkeerslicht wasn't initialised when calling setMaster");
    Verkeerslicht::fMaster = master;
    ENSURE(fMaster==master,"setMaster postcondition failure");
}

void Verkeerslicht::switchKleur() {
    REQUIRE(fKleur==rood or fKleur==groen or fKleur==oranje,"Licht heeft geen geldige kleur");
    kleur color=fKleur;
    if (fKleur == rood)
        fKleur = groen;
    else if (fKleur == groen)
        fKleur = oranje;
    else if(fKleur==oranje){
        fKleur=rood;
    }
    if(fKruispunt!=NULL){
        if(isMaster()){
            fKruispunt->getOtherVerkeerslicht(this)->switchKleur();
        }
    }
    ENSURE(fKleur!=color,"Licht is niet van kleur veranderd");
}

Voertuig *Verkeerslicht::getClosestVehicle() {
    REQUIRE(properlyInitialised(),"Verkeerslicht wasn't initialised when calling getClosestVehicle");
    vector<Voertuig*> fVoertuigen = fBaan->getVoertuigen();
    for (long unsigned int i = fVoertuigen.size() - 1; i > 0; i--) {
        if (fPositie > fVoertuigen[i]->getPositie()){
            return fVoertuigen[i];
        }
    }
    return fVoertuigen.back();
}
