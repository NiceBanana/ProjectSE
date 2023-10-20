//
// Created by student on 03.03.22.
//

#include "Baan.h"
#include "Voertuig.h"
#include "Verkeerslicht.h"
#include "VoertuigGenerator.h"
#include "Bushalte.h"
#include "Kruispunt.h"
#include "lib/DesignByContract.h"

bool Baan::properlyInitialised() const {
    return fInitCheck==this;
}

Baan::Baan() : fLengte(1) {
    fInitCheck=this;
    ENSURE(this->properlyInitialised(),"constructor must end in properlyInitialised state");
}

Baan::Baan(const string &naam, int lengte) : fNaam(naam), fLengte(lengte) {
    REQUIRE(lengte>0,"Baan moet een strikt positieve lengte hebben");
    fInitCheck=this;
    ENSURE(this->properlyInitialised(),"constructor must end in properlyInitialised state");
    ENSURE(fLengte>0, "Baan moet een strikt positieve lengte hebben");
}

Baan::~Baan() {
    for (long unsigned int i = 0; i < fVoertuigen.size(); i++) delete fVoertuigen[i];
    for (long unsigned int i = 0; i < fVerkeerslichten.size(); i++) delete fVerkeerslichten[i];
    for (long unsigned int i = 0; i < fVoertuigGeneratoren.size(); i++) delete fVoertuigGeneratoren[i];
}

const string &Baan::getNaam() const {
    REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling getNaam");
    return fNaam;
}

void Baan::setNaam(const string &naam) {
    REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling setNaam");
    Baan::fNaam = naam;
    ENSURE(fNaam==naam,"setNaam postcondition failure");
}

int Baan::getLengte() const {
    REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling getLengte");
    ENSURE(fLengte>0,"Baan moet een strikt positieve lengte hebben");
    return fLengte;
}

void Baan::setLengte(int lengte) {
    REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling setLengte");
    REQUIRE(fLengte > 0, "Baan moet een strikt positieve lengte hebben");
    Baan::fLengte = lengte;
    ENSURE(fLengte==lengte,"setLengte postcondition failure");
}

void Baan::deleteElement(VerkeersElement *element) {
    REQUIRE(element->getBaan() == this, "Banen komen niet overeen");
    switch (element->getType()) {
        case VOERTUIG:
            for (vector<Voertuig*>::iterator it = fVoertuigen.begin(); it != fVoertuigen.end(); it++) {
                if (*it == element) {
                    fVoertuigen.erase(it);
                    break;
                }
            }
            break;
        case VERKEERSLICHT:
            for (vector<Verkeerslicht*>::iterator it = fVerkeerslichten.begin(); it != fVerkeerslichten.end(); it++) {
                if (*it == element) {
                    fVerkeerslichten.erase(it);
                    break;
                }
            }
            break;
        case GENERATOR:
            for (vector<VoertuigGenerator*>::iterator it = fVoertuigGeneratoren.begin(); it != fVoertuigGeneratoren.end(); it++) {
                if (*it == element) {
                    fVoertuigGeneratoren.erase(it);
                    break;
                }
            }
            break;
        case BUSHALTE:
            for (vector<Bushalte*>::iterator it = fBushaltes.begin(); it != fBushaltes.end(); it++) {
                if (*it == element) {
                    fBushaltes.erase(it);
                    break;
                }
            }
            break;
    }

}

const vector<Voertuig *> &Baan::getVoertuigen() const {
    REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling getVoertuigen");
    return fVoertuigen;
}

void Baan::addVoertuig(Voertuig *voertuig) {
    REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling addVoertuig");
    REQUIRE(this==voertuig->getBaan(),"Banen komen niet overeen");
    REQUIRE(not vectorChecker(voertuig),"Voertuig zit al in de vector");
    REQUIRE(this->getLengte()>voertuig->getPositie(),"Lengte baan moet groter zijn dan positie voertuig");
    for (long unsigned int i = 0; i < fVoertuigen.size(); i++) {
        if (voertuig->getPositie() < fVoertuigen[i]->getPositie()) {
            fVoertuigen.insert(fVoertuigen.begin() + i, voertuig);
            return;
        }
    }
    fVoertuigen.push_back(voertuig);
    ENSURE(vectorChecker(voertuig),"addVoertuig postcondition failure");
}

Voertuig *Baan::getVoorganger(Voertuig * voertuig) const {
    REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling getVoorganger");
    REQUIRE(this==voertuig->getBaan(),"Banen komen niet overeen");
    REQUIRE(vectorChecker(voertuig),"Voertuig bevindt zich niet op de baan");
    for (long unsigned int i = 0; i < fVoertuigen.size() - 1; i++) {
        if (voertuig == fVoertuigen[i]){
            ENSURE(fVoertuigen[i+1]->getBaan()==this,"Banen komen niet overeen");
            ENSURE(vectorChecker(fVoertuigen[i+1]),"Voorganger bevindt zich niet op de baan");
            return fVoertuigen[i+1];
        }
    }
    return NULL;
}

Voertuig *Baan::getVolgganger(Voertuig *voertuig) const {
    REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling getVolgganger");
    REQUIRE(this==voertuig->getBaan(),"Banen komen niet overeen");
    REQUIRE(vectorChecker(voertuig),"Voertuig bevindt zich niet op de baan");
    for (long unsigned int i = 1; i < fVoertuigen.size(); i++) {
        if (voertuig == fVoertuigen[i]){
            ENSURE(fVoertuigen[i-1]->getBaan()==this,"Banen komen niet overeen");
            ENSURE(vectorChecker(fVoertuigen[i-1]),"Volgganger bevindt zich niet op de baan");
            return fVoertuigen[i-1];
        }
    }
    return NULL;
}

const vector<Verkeerslicht *> &Baan::getVerkeerslichten() const {
    REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling getVerkeerslichten");
    return fVerkeerslichten;
}

void Baan::addVerkeerslicht(Verkeerslicht *verkeerslicht) {
    REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling addVerkeerslicht");
    REQUIRE(this==verkeerslicht->getBaan(),"Banen komen niet overeen");
    REQUIRE(not vectorChecker(verkeerslicht),"Verkeerslicht zit al in de vector");
    REQUIRE(this->getLengte()>verkeerslicht->getPositie(),"Lengte baan moet groter zijn dan positie verkeerslicht");
    for (long unsigned int i = 0; i < fVerkeerslichten.size(); i++) {
        if (verkeerslicht->getPositie() < fVerkeerslichten[i]->getPositie()) {
            fVerkeerslichten.insert(fVerkeerslichten.begin() + i, verkeerslicht);
            return;
        }
    }
    fVerkeerslichten.push_back(verkeerslicht);
    ENSURE(vectorChecker(verkeerslicht),"addVerkeerslicht postcondition failure");
}

Verkeerslicht *Baan::getVolgendeLicht(Voertuig *voertuig) const {
    REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling getVolgendeLicht");
    REQUIRE(voertuig->getBaan()==this,"Banen komen niet overeen");
    REQUIRE(vectorChecker(voertuig),"Voertuig bevindt zich niet op de baan");
    for (long unsigned int i = 0; i < fVerkeerslichten.size(); i++) {
        if (voertuig->getPositie() < fVerkeerslichten[i]->getPositie()){
            ENSURE(fVerkeerslichten[i]->getBaan()==voertuig->getBaan(),"Banen komen niet overeen");
            ENSURE(vectorChecker(fVerkeerslichten[i]),"Verkeerslicht bevindt zich niet op de baan");
            return fVerkeerslichten[i];
        }
    }
    return NULL;
}

const vector<VoertuigGenerator *> &Baan::getVoertuigGeneratoren() const {
    REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling getVoertuigGeneratoren");
    return fVoertuigGeneratoren;
}

void Baan::addVoertuigGenerator(VoertuigGenerator* generator) {
    REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling addVoertuigGenerator");
    REQUIRE(generator->getBaan()==this,"Banen komen niet overeen");
    REQUIRE(not vectorChecker(generator),"Generator bevindt zich al op de baan");
    fVoertuigGeneratoren.push_back(generator);
    ENSURE(vectorChecker(generator),"addVoertuigGenerator postcondition failure");
}

bool Baan::vectorChecker(const Voertuig *voertuig) const{
    REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling vectorChecker voor voertuig");
    for (long unsigned int i = 0; i < fVoertuigen.size(); i++) {
        if(fVoertuigen[i]==voertuig) {
            return true;
        }
    }
    return false;
}

bool Baan::vectorChecker(const Verkeerslicht *verkeerslicht) const{
    REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling vectorChecker voor verkeerslicht");
    for (long unsigned int i = 0; i < fVerkeerslichten.size(); i++) {
        if(fVerkeerslichten[i]==verkeerslicht) {
            return true;
        }
    }
    return false;
}

bool Baan::vectorChecker(const VoertuigGenerator *voertuigGenerator) const {
    REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling vectorChecker voor voertuiggenerator");
    for (long unsigned int i = 0; i < fVoertuigGeneratoren.size(); i++) {
        if(fVoertuigGeneratoren[i]==voertuigGenerator) {
            return true;
        }
    }
    return false;
}

bool Baan::vectorChecker(const Bushalte *bushalte) const {
    REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling vectorChecker voor bushalte");
    for (long unsigned int i = 0; i < fBushaltes.size(); i++) {
        if(fBushaltes[i]==bushalte) {
            return true;
        }
    }
    return false;
}

const vector<Bushalte *> &Baan::getBushaltes() const {
    REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling getBushaltes");
    return fBushaltes;
}

void Baan::addBushalte(Bushalte *bushalte) {
    REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling addBushalte");
    for (long unsigned int i = 0; i < fBushaltes.size(); i++) {
        if (bushalte->getPositie() < fBushaltes[i]->getPositie()) {
            fBushaltes.insert(fBushaltes.begin() + i, bushalte);
            ENSURE(vectorChecker(bushalte),"addBushalte postcondition failure");
            return;
        }
    }
    fBushaltes.push_back(bushalte);
}

Bushalte *Baan::getVolgendeBushalte(Voertuig *voertuig) const {
    REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling getVolgendeBushalte");
    REQUIRE(voertuig->getBaan()==this,"Banen komen niet overeen");
    REQUIRE(vectorChecker(voertuig),"Voertuig bevindt zich niet op de baan");
    for (long unsigned int i = 0; i < fBushaltes.size(); i++) {
        if (voertuig->getPositie() < fBushaltes[i]->getPositie()){
            ENSURE(fBushaltes[i]->getBaan()==voertuig->getBaan(),"Banen komen niet overeen");
            ENSURE(vectorChecker(fBushaltes[i]),"Bushalte bevindt zich niet op de baan");
            return fBushaltes[i];
        }
    }
    return NULL;
}

const vector<Kruispunt *> &Baan::getKruispunten() const {
    REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling getBushaltes");
    return fKruispunten;
}

void Baan::addKruispunt(Kruispunt *kruispunt) {
    REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling addKruispunt");
    for (long unsigned int i = 0; i < fKruispunten.size(); i++) {
        if (kruispunt->getPositie(this) < fKruispunten[i]->getPositie(this)) {
            fKruispunten.insert(fKruispunten.begin() + i, kruispunt);
            ENSURE(vectorChecker(kruispunt),"addKruispunt postcondition failure");
            return;
        }
    }
    fKruispunten.push_back(kruispunt);
    ENSURE(vectorChecker(kruispunt),"addKruispunt postcondition failure");
}

Kruispunt *Baan::getVolgendeKruispunt(Voertuig *voertuig) const {
    REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling getVolgendeKruispunt");
    REQUIRE(voertuig->getBaan()==this,"Banen komen niet overeen");
    REQUIRE(vectorChecker(voertuig),"Voertuig bevindt zich niet op de baan");
    for (long unsigned int i = 0; i < fKruispunten.size(); i++) {
        if (voertuig->getPositie() < fKruispunten[i]->getPositie(this)){
            ENSURE(fKruispunten[i]->getBanen().first==voertuig->getBaan() or fKruispunten[i]->getBanen().second==voertuig->getBaan(),"Banen komen niet overeen");
            ENSURE(vectorChecker(fKruispunten[i]),"Kruispunt bevindt zich niet op de baan");
            return fKruispunten[i];
        }
    }
    return NULL;
}

bool Baan::vectorChecker(const Kruispunt* kruispunt) const {
    REQUIRE(this->properlyInitialised(),"Baan wasn't initialised when calling vectorChecker voor Kruispunt");
    for (long unsigned int i = 0; i < fKruispunten.size(); i++) {
        if(fKruispunten[i]==kruispunt) {
            return true;
        }
    }
    return false;
}
