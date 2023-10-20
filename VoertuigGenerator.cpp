//
// Created by dante on 17/03/2022.
//

#include "VoertuigGenerator.h"
#include "Baan.h"
#include "VerkeersSituatie.h"
#include "lib/DesignByContract.h"
#include "Voertuig.h"
#include "Prioriteitsvoertuig.h"
#include "Bus.h"

VoertuigGenerator::VoertuigGenerator() {
    fType = GENERATOR;
    fTimeLastVehicle=0;
}

VoertuigGenerator::VoertuigGenerator(Baan *baan, int frequentie) : VerkeersElement(baan, 0) {
    REQUIRE(frequentie>0,"Frequentie moet strikt positief zijn");
    fFrequentie = frequentie;
    fType = GENERATOR;
    fTimeLastVehicle=0;
    baan->addVoertuigGenerator(this);
}

VoertuigGenerator::~VoertuigGenerator() {}

void VoertuigGenerator::setBaan(Baan *baan) {
    VerkeersElement::setBaan(baan);
    baan->addVoertuigGenerator(this);
}

int VoertuigGenerator::getFrequentie() const {
    REQUIRE(this->properlyInitialised(),"VoertuigGenerator wasn't initialised when calling getFrequentie");
    ENSURE(fFrequentie>0,"Frequentie moet strikt positief zijn");
    return fFrequentie;
}

void VoertuigGenerator::setFrequentie(int frequentie) {
    REQUIRE(this->properlyInitialised(),"VoertuigGenerator wasn't initialised when calling setFrequentie");
    REQUIRE(frequentie>0,"Frequentie moet strikt positief zijn");
    VoertuigGenerator::fFrequentie = frequentie;
    ENSURE(fFrequentie==frequentie,"setFrequentie postcondition failure");
}

void VoertuigGenerator::update(double tijd) {
    REQUIRE(this->properlyInitialised(),"VoertuigGenerator wasn't initialised when calling update");
    REQUIRE(tijd-fTimeLastVehicle>0,"Tijd is niet vooruitgegaan");
    const vector<Voertuig *> Voertuigen = fBaan->getVoertuigen();
    if(tijd-fTimeLastVehicle > fFrequentie && (Voertuigen.empty() ||
            Voertuigen[0]->getPositie() > 2*Voertuigen[0]->getLengte())){
        new Voertuig(fBaan, 0, 0, 0);
        fTimeLastVehicle=tijd;
        ENSURE(fTimeLastVehicle==tijd,"Tijd niet aangepast");
    }
}

void VoertuigGenerator::generateVehicle(voertuigType type) {
    switch(type){
        case Ziekenwagen:
        case Politiecombi:
        case Brandweerwagen:
            new Prioriteitsvoertuig(fBaan,0,0,0,type);
            break;
        case Auto:
            new Voertuig(fBaan,0,0,0);
            break;
        case bus:
            new Bus(fBaan,0,0,0);
            break;
    }
}
