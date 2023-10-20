//
// Created by dante on 17/03/2022.
//

#ifndef INC_VOERTUIGGENERATOR_H
#define INC_VOERTUIGGENERATOR_H

#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include "VerkeersElement.h"
#include "Voertuig.h"

class VoertuigGenerator: public VerkeersElement {
private:
    int fFrequentie;
    double fTimeLastVehicle;
public:

    VoertuigGenerator();

    /*
     * REQUIRE(frequentie>0,"Frequentie moet strikt positief zijn");
     */
    VoertuigGenerator(Baan *baan, int frequentie);


    virtual ~VoertuigGenerator();


    virtual void setBaan(Baan *baan);

    /*
     * REQUIRE(this->properlyInitialised(),"VoertuigGenerator wasn't initialised when calling getFrequentie");
     * ENSURE(fFrequentie>0,"Frequentie moet strikt positief zijn");
     */
    int getFrequentie() const;

    /*
     * REQUIRE(this->properlyInitialised(),"VoertuigGenerator wasn't initialised when calling setFrequentie");
     * REQUIRE(frequentie>0,"Frequentie moet strikt positief zijn");
     * ENSURE(fFrequentie==frequentie,"setFrequentie postcondition failure");
     */
    void setFrequentie(int frequentie);

    /*
     * REQUIRE(this->properlyInitialised(),"VoertuigGenerator wasn't initialised when calling update");
     * REQUIRE(tijd-fTimeLastVehicle>0,"Tijd is niet vooruitgegaan");
     * ENSURE(fTimeLastVehicle==tijd,"Tijd niet aangepast");
     */
    void update(double tijd);

    void generateVehicle(voertuigType type);
};


#endif //INC_VOERTUIGGENERATOR_H
