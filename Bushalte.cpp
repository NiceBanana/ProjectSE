//
// Created by stan on 21/04/22.
//

#include "Bushalte.h"
#include "Baan.h"
#include "lib/DesignByContract.h"

Bushalte::Bushalte() {
    fType = BUSHALTE;
}

Bushalte::Bushalte(Baan *Baan, double Positie, int Wachttijd) : VerkeersElement(Baan, Positie) {
    fWachttijd = Wachttijd;
    fType = BUSHALTE;
}

int Bushalte::getWachttijd() const {
    REQUIRE(this->properlyInitialised(),"Bushalte wasn't initialised when calling getWachttijd");
    return fWachttijd;
}

void Bushalte::setWachttijd(int wachttijd) {
    REQUIRE(this->properlyInitialised(),"Bushalte wasn't initialised when calling setWachttijd");
    Bushalte::fWachttijd = wachttijd;
    ENSURE(fWachttijd==wachttijd,"setWachttijd postcondition failure");
}

void Bushalte::setBaan(Baan *baan) {
    VerkeersElement::setBaan(baan);
    baan->addBushalte(this);
}
