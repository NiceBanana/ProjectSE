//
// Created by dante on 9/05/2022.
//

#include "Bus.h"
#include "lib/DesignByContract.h"
#include "Baan.h"
#include "Verkeerslicht.h"

Bus::Bus(Baan *baan, int positie, double snelheid, double versnelling) : Voertuig(baan, positie, snelheid, versnelling){
    fLengte = 12;
    fVMax = 11.4;
    fvMax = fVMax;
    faMax = 1.22;
    fbMax = 4.29;
    ffMin = 12;
}

bool Bus::update() {
    if (fWacht.second > 0 && fWacht.first) {
        fWacht.second -= simulatietijd;
        fVersnelling = 0;
        return true;
    }
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

bool Bus::needVertraging(Voertuig *voorganger) {
    REQUIRE(this->properlyInitialised(),"Voertuig wasn't initialised when calling needVertraging");
    Verkeerslicht *licht = fBaan->getVolgendeLicht(this);
    Bushalte *halte = fBaan->getVolgendeBushalte(this);
    if (halte &&
        //(not voorganger || voorganger->getPositie() > halte->getPositie()) && // de halte voor de voorganger
        (not licht || licht->getPositie() > halte->getPositie())) { // de halte voor het verkerslicht
        if (halte != fWacht.first &&
            halte->getPositie() - fPositie < vertraagafstand && halte->getPositie() - fPositie > stopafstand) {
            return true;
        }
    }
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

bool Bus::needStop(Voertuig *voorganger) {
    REQUIRE(this->properlyInitialised(),"Voertuig wasn't initialised when calling needStop");
    Verkeerslicht *licht = fBaan->getVolgendeLicht(this);
    Bushalte *halte = fBaan->getVolgendeBushalte(this);
    if (halte &&
        //(not voorganger || voorganger->getPositie() > halte->getPositie()) && // de halte voor de voorganger
        (not licht || licht->getPositie() > halte->getPositie())) { // de halte voor het verkeerslicht
        if (halte != fWacht.first &&
            halte->getPositie()-fPositie < stopafstand) {
            if (fSnelheid <= 0.0001) {
                fWacht.first = halte;
                fWacht.second = halte->getWachttijd();
            }
            return true;
        }
    }
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

Bus::Bus() {
    fLengte = 12;
    fVMax = 11.4;
    fvMax = fVMax;
    faMax = 1.22;
    fbMax = 4.29;
    ffMin = 12;
}

voertuigType Bus::getVoertuigType() const {
    return bus;
}
