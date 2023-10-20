//
// Created by student on 03.03.22.
//

#include "Voertuig.h"
#include "VerkeersSituatie.h"
#include "Baan.h"
#include "Verkeerslicht.h"
#include "Kruispunt.h"
#include "Bushalte.h"
#include "lib/DesignByContract.h"

Voertuig::Voertuig() : fSnelheid(0), fVersnelling(0), fLengte(4) {
    fType = VOERTUIG;
    // Setup Variabele
    fLengte = 4;
    fVMax = 16.6;
    fvMax = fVMax;
    faMax = 1.44;
    fbMax = 4.61;
    ffMin = 4;
}

Voertuig::Voertuig(Baan *baan, int positie, double snelheid, double versnelling) : VerkeersElement(baan, positie) {
    REQUIRE(baan, "Baan moet bestaan");
    REQUIRE(snelheid >= 0, "Snelheid moet altijd positief zijn");
    fSnelheid = snelheid;
    fVersnelling = versnelling;
    fType = VOERTUIG;
    // Setup variabele
    fLengte = 4;
    fVMax = 16.6;
    fvMax = fVMax;
    faMax = 1.44;
    fbMax = 4.61;
    ffMin = 4;
    baan->addVoertuig(this);
}

Voertuig::~Voertuig() {}

void Voertuig::setBaan(Baan *baan) {
    VerkeersElement::setBaan(baan);
    baan->addVoertuig(this);
}

double Voertuig::getSnelheid() const {
    REQUIRE(this->properlyInitialised(),"Voertuig wasn't initialised when calling getPositie");
    ENSURE(fSnelheid>=0,"Snelheid van voertuig is niet positief");
    return fSnelheid;
}

void Voertuig::setSnelheid(double snelheid) {
    REQUIRE(this->properlyInitialised(),"Voertuig wasn't initialised when calling setSnelheid");
    REQUIRE(snelheid>=0,"Snelheid moet altijd positief zijn");
    Voertuig::fSnelheid = snelheid;
    ENSURE(fSnelheid==snelheid,"setSnelheid postcondition failure");
}

double Voertuig::getVersnelling() const {
    REQUIRE(this->properlyInitialised(),"Voertuig wasn't initialised when calling getVersnelling");
    return fVersnelling;
}

void Voertuig::setVersnelling(double versnelling) {
    REQUIRE(this->properlyInitialised(),"Voertuig wasn't initialised when calling setVersnelling");
    Voertuig::fVersnelling = versnelling;
    ENSURE(fVersnelling==versnelling,"setVersnelling postcondition failure");
}

int Voertuig::getLengte() const {
    REQUIRE(this->properlyInitialised(),"Voertuig wasn't initialised when calling getLengte");
    return fLengte;
}

void Voertuig::newSnelheid() {
    REQUIRE(this->properlyInitialised(),"Voertuig wasn't initialised when calling newSnelheid");
    fSnelheid += fVersnelling*simulatietijd;
    if(fSnelheid > fvMax){
        fSnelheid = fvMax;
    }
    ENSURE(fSnelheid>=0,"Snelheid moet altijd positief zijn");
}

bool Voertuig::newPositie() {
    REQUIRE(this->properlyInitialised(),"Voertuig wasn't initialised when calling newPositie");
    int xMax = fBaan->getLengte();
    double nieuwePlaats = fPositie+ fSnelheid*simulatietijd + fVersnelling*(pow(simulatietijd,2) / 2);
    Kruispunt* nextKruispunt=fBaan->getVolgendeKruispunt(this);
    if(nextKruispunt && fPositie<nextKruispunt->getPositie(fBaan) && nieuwePlaats>nextKruispunt->getPositie(fBaan)){
        double fromJunction=nieuwePlaats-nextKruispunt->getPositie(fBaan);
        srand(2);
        double r = ((double) rand() / (RAND_MAX));
        if(r<0.5){
            fPositie=nieuwePlaats;
        }
        else{
            fBaan->deleteElement(this);
            Baan *otherBaan = nextKruispunt->getOtherBaan(fBaan);
            fPositie=nextKruispunt->getPositie(otherBaan)+fromJunction;
            this->setBaan(otherBaan);
        }
    }
    fPositie += fSnelheid*simulatietijd + fVersnelling*(pow(simulatietijd,2) / 2);
    if(fPositie>xMax){
        return false;
    }
    return true;
}

void Voertuig::newVersnelling() {
    REQUIRE(this->properlyInitialised(),"Voertuig wasn't initialised when calling newVersnelling");
    Voertuig* voorganger = fBaan->getVoorganger(this);
    double delta = 0;
    if (voorganger) {
        double volgafstand = voorganger->fPositie - fPositie - voorganger->fLengte;
        double speedverschil = fSnelheid - voorganger->fSnelheid;
        delta = (ffMin + max(double(0), fSnelheid + (fSnelheid * speedverschil / (2 * sqrt(faMax*fbMax))))) / volgafstand;
    }
    if(needStop(voorganger)){
        fVersnelling = -(fbMax*fSnelheid/fvMax);
        return;
    }
    fVersnelling = faMax * (1 - pow(fSnelheid/fvMax,4) - pow(delta,2));
}

bool Voertuig::update() {
    REQUIRE(this->properlyInitialised(),"Voertuig wasn't initialised when calling update");
    int xMax = fBaan->getLengte();
    Voertuig* voorganger = fBaan->getVoorganger(this);
    if(needVertraging(voorganger) || needStop(voorganger)){
        fvMax = vertraagfactor * fVMax;
    } else {
        fvMax = fVMax;
    }
    ENSURE(fvMax>=0 and fVMax>=0,"Maximale snelheid mag niet negatief zijn");
    if(fSnelheid + fVersnelling*simulatietijd < 0){ //Als de snelheid negatief wordt
        fPositie -= pow(fSnelheid,2)/(2*fVersnelling);
        fSnelheid = 0;
    } else {
        newSnelheid();
        newPositie();
    }
    newVersnelling();
    if(fPositie>xMax){
        return false;
    }
    return true;
}

bool Voertuig::needVertraging(Voertuig* voorganger) {
    REQUIRE(this->properlyInitialised(),"Voertuig wasn't initialised when calling needVertraging");
    Verkeerslicht *licht = fBaan->getVolgendeLicht(this);
    if (not licht || licht->getKleur() == groen) {
        return false;
    }
    int positieLicht = licht->getPositie();
    if (voorganger && voorganger->getPositie() < positieLicht) {    //Als er een voorganger is en die is dichter dan het licht
        return false;
    }
    if (positieLicht-fPositie < vertraagafstand && positieLicht-fPositie > stopafstand) {
        if (licht->getKleur() != groen)
            return true;
    }
    return false;
}

bool Voertuig::needStop(Voertuig* voorganger) {
    REQUIRE(this->properlyInitialised(),"Voertuig wasn't initialised when calling needStop");
    Verkeerslicht *licht = fBaan->getVolgendeLicht(this);
    if (not licht || licht->getKleur() == groen) {
        return false;
    }
    int positieLicht = licht->getPositie();
    if (voorganger && voorganger->getPositie() < positieLicht) {    //Als er een voorganger is en die is dichter dan het licht
        return false;
    }
    if (positieLicht - fPositie < stopafstand) {
        if (licht->getKleur() == rood)
            return true;
    }
    return false;
}

voertuigType Voertuig::getVoertuigType() const {
    return Auto;
}
