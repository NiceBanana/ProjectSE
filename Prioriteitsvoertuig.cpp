//
// Created by dante on 10/05/2022.
//

#include "Prioriteitsvoertuig.h"
#include "Verkeerslicht.h"
#include "Baan.h"
#include "lib/DesignByContract.h"

void Prioriteitsvoertuig::setupVariable(voertuigType type) {
    switch (type) {
        case Brandweerwagen:
            fLengte = 10;
            fVMax = 14.6;
            fvMax = fVMax;
            faMax = 1.33;
            fbMax = 4.56;
            ffMin = 10;
            break;
        case Ziekenwagen:
            fLengte = 8;
            fVMax = 15.5;
            fvMax = fVMax;
            faMax = 1.44;
            fbMax = 4.47;
            ffMin = 8;
            break;
        case Politiecombi:
            fLengte = 6;
            fVMax = 17.2;
            fvMax = fVMax;
            faMax = 1.55;
            fbMax = 4.92;
            ffMin = 6;
            break;
        default:
            break;
    }
}

Prioriteitsvoertuig::Prioriteitsvoertuig(Baan *baan, int positie, double snelheid, double versnelling,
                                         voertuigType voertuig) : Voertuig(baan, positie, snelheid, versnelling) {
    fVoertuigType = voertuig;
    setupVariable(voertuig);
}

bool Prioriteitsvoertuig::needVertraging(Voertuig *voorganger) {
    REQUIRE(this->properlyInitialised(),"Voertuig wasn't initialised when calling needVertraging");
    return false;
}

bool Prioriteitsvoertuig::needStop(Voertuig *voorganger) {
    REQUIRE(this->properlyInitialised(),"Voertuig wasn't initialised when calling needStop");
    return false;
}

Prioriteitsvoertuig::Prioriteitsvoertuig(voertuigType Voertuig) {
    fVoertuigType = Voertuig;
    setupVariable(Voertuig);
}

voertuigType Prioriteitsvoertuig::getVoertuigType() const {
    return fVoertuigType;
}
