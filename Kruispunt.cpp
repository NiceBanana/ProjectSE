//
// Created by dante on 21/04/2022.
//

#include "Kruispunt.h"
#include "Baan.h"
#include "Verkeerslicht.h"
#include "lib/DesignByContract.h"

bool Kruispunt::properlyInitialised() const {
    return fInitCheck==this;
}

Kruispunt::Kruispunt() {
    fInitCheck=this;
    fBanen.first = NULL;
    fBanen.second = NULL;
    fPositie.first = 0;
    fPositie.second = 0;
}

Kruispunt::Kruispunt(const pair<Baan*, Baan*> &banen, const pair<double, double> &positie) : fBanen(banen), fPositie(positie) {
    REQUIRE(banen.first!=banen.second,"Kruispunt moet twee verschillende banen hebben");
    REQUIRE(positie.first>=0 and positie.second>=0,"Posities moeten positief zijn");
    fInitCheck=this;
}

Kruispunt::~Kruispunt() {
    REQUIRE(this->properlyInitialised(),"Kruispunt wasn't initialised when calling destructor");
}

const pair<Baan*, Baan*> &Kruispunt::getBanen() const {
    REQUIRE(this->properlyInitialised(),"Kruispunt wasn't initialised when calling getBanen");
    return fBanen;
}

void Kruispunt::setBanen(const pair<Baan*, Baan*> &banen, const pair<double, double> &positie) {
    REQUIRE(this->properlyInitialised(),"Kruispunt wasn't initialised when calling setBanen");
    REQUIRE(banen.first!=banen.second,"Kruispunt moet twee verschillende banen hebben");
    REQUIRE(positie.first>=0 and positie.second>=0,"Posities moeten positief zijn");
    Kruispunt::fBanen = banen;
    Kruispunt::fPositie = positie;
    banen.first->addKruispunt(this);
    banen.second->addKruispunt(this);
    ENSURE(fBanen==banen,"setBanen postcondition failure");
    ENSURE(fPositie==positie, "setBanen postcondition failure");
}

Baan* Kruispunt::getOtherBaan(const Baan *baan) const {
    REQUIRE(this->properlyInitialised(),"Kruispunt wasn't initialised when calling getOtherBaan");
    REQUIRE(fBanen.first == baan || fBanen.second == baan, "Deze baan behoort niet tot dit kruispunt");
    if (fBanen.first == baan) {
        return fBanen.second;
    } else {
        return fBanen.first;
    }
}

double Kruispunt::getPositie(const Baan *baan) const {
    REQUIRE(this->properlyInitialised(),"Kruispunt wasn't initialised when calling getPositie");
    REQUIRE(fBanen.first == baan || fBanen.second == baan, "Deze baan behoort niet tot dit kruispunt");
    if (fBanen.first == baan) {
        return fPositie.first;
    } else {
        return fPositie.second;
    }
}

const pair<Verkeerslicht *, Verkeerslicht *> &Kruispunt::getVerkeerslichten() const {
    REQUIRE(this->properlyInitialised(),"Kruispunt wasn't initialised when calling getVerkeerslichten");
    return fVerkeerslichten;
}

void Kruispunt::setVerkeerslichten(const pair<Verkeerslicht *, Verkeerslicht *> &verkeerslichten) {
    REQUIRE(this->properlyInitialised(),"Kruispunt wasn't initialised when calling setVerkeerslichten");
    REQUIRE(verkeerslichten.first!=verkeerslichten.second,"Verkeerslichten van kruispunt moeten verschillend zijn");
    Kruispunt::fVerkeerslichten = verkeerslichten;
    verkeerslichten.first->setKruispunt(this);
    verkeerslichten.second->setKruispunt(this);
    ENSURE(fVerkeerslichten==verkeerslichten,"setVerkeerslichten postcondition failure");
}

Verkeerslicht *Kruispunt::getOtherVerkeerslicht(Verkeerslicht* verkeerslicht) const {
    REQUIRE(this->properlyInitialised(),"Kruispunt wasn't initialised when calling getOtherVerkeerslicht");
    REQUIRE(fVerkeerslichten.first!=NULL and fVerkeerslichten.second!=NULL,"Er zijn geen verkeerslichten op dit kruispunt");
    if(verkeerslicht==fVerkeerslichten.first){
        return fVerkeerslichten.second;
    }
    else{
        return fVerkeerslichten.first;
    }
}
