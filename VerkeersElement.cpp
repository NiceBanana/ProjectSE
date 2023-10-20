//
// Created by stan on 28/03/22.
//

#include "VerkeersElement.h"
#include "Baan.h"
#include "lib/DesignByContract.h"

bool VerkeersElement::properlyInitialised() const{
    return fInitCheck==this;
}

VerkeersElement::VerkeersElement() : fBaan(NULL), fPositie(0) {
    fInitCheck = this;
    ENSURE(properlyInitialised(), "constructor must end in properlyInitialised state");
}

VerkeersElement::VerkeersElement(Baan *baan, double positie) : fBaan(baan), fPositie(positie) {
    REQUIRE(positie>=0,"Positie moet altijd positief zijn");
    if(baan != NULL) {
        REQUIRE(positie<baan->getLengte(),"De positie van het element moet kleiner zijn dan de lengte van de baan");
    }
    fInitCheck = this;
    ENSURE(properlyInitialised(), "constructor must end in properlyInitialised state");
}

VerkeersElement::~VerkeersElement() {
    if (fBaan != NULL) {
        fBaan->deleteElement(this);
    }
}

Baan *VerkeersElement::getBaan() const {
    REQUIRE(this->properlyInitialised(),"VerkeersElement wasn't initialised when calling getBaan");
    return fBaan;
}

void VerkeersElement::setBaan(Baan *baan) {
    REQUIRE(this->properlyInitialised(),"VerkeersElement wasn't initialised when calling setBaan");
    REQUIRE(this->fPositie<baan->getLengte(),"Lengte van de baan moet groter zijn dan positie VerkeersElement");
    fBaan = baan;
    ENSURE(fBaan==baan,"setBaan postcondition failure");
}

double VerkeersElement::getPositie() const {
    REQUIRE(this->properlyInitialised(),"VerkeersElement wasn't initialised when calling getPositie");
    ENSURE(fPositie>=0,"De positie van VerkeersElement is niet positief");
    return fPositie;
}

void VerkeersElement::setPositie(int positie) {
    REQUIRE(this->properlyInitialised(),"VerkeersElement wasn't initialised when calling setPositie");
    REQUIRE(positie >= 0, "Positie moet altijd positief zijn");
    if(fBaan != NULL) {
        REQUIRE(positie<this->getBaan()->getLengte(),"De positie van een VerkeersElement moet kleiner zijn dan de lengte van de baan");
    }
    fPositie = double(positie);
    ENSURE(fPositie==double(positie),"setPositie postcondition failure");
}

elementType VerkeersElement::getType() const {
    REQUIRE(this->properlyInitialised(),"VerkeersElement wasn't initialised when calling getType");
    return fType;
}
