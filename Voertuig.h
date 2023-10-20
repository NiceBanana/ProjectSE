//
// Created by student on 03.03.22.
//

#ifndef INC_VOERTUIG_H
#define INC_VOERTUIG_H

#include <iostream>
#include <cmath>
#include "VerkeersElement.h"
#include "Bushalte.h"

using namespace std;

#define simulatietijd 0.0166
#define vertraagafstand 50
#define stopafstand 15
#define vertraagfactor 0.4

enum voertuigType {
    Brandweerwagen,
    Ziekenwagen,
    Politiecombi,
    Auto,
    bus
};

class Voertuig: public VerkeersElement {
protected:
    double fSnelheid;
    double fVersnelling;
    int fLengte;
    double fvMax;
    double fVMax;
    double faMax;
    double fbMax;
    int ffMin;
public:
    Voertuig();

    /*
     * REQUIRE(not baan, "Baan moet bestaan");
     * REQUIRE(snelheid >= 0, "Snelheid moet altijd positief zijn");
     */
    Voertuig(Baan *fBaan, int fPositie, double fSnelheid, double fVersnelling);


    virtual ~Voertuig();


    void setBaan(Baan *baan);

    /*
     * REQUIRE(this->properlyInitialised(),"Voertuig wasn't initialised when calling getPositie");
     * ENSURE(fSnelheid>=0,"Snelheid van voertuig is niet positief");
     */
    double getSnelheid() const;

    /*
     * REQUIRE(this->properlyInitialised(),"Voertuig wasn't initialised when calling setSnelheid");
     * REQUIRE(snelheid>=0,"Snelheid moet altijd positief zijn");
     * ENSURE(fSnelheid==snelheid,"setSnelheid postcondition failure");
     */
    void setSnelheid(double snelheid);

    /*
     * REQUIRE(this->properlyInitialised(),"Voertuig wasn't initialised when calling getVersnelling");
     */
    double getVersnelling() const;

    /*
     * REQUIRE(this->properlyInitialised(),"Voertuig wasn't initialised when calling setVersnelling");
     * ENSURE(fVersnelling==versnelling,"setVersnelling postcondition failure");
     */
    void setVersnelling(double versnelling);

    /*
     * REQUIRE(this->properlyInitialised(),"Voertuig wasn't initialised when calling getLengte");
     */
    int getLengte() const;

    /*
     * REQUIRE(this->properlyInitialised(),"Voertuig wasn't initialised when calling update");
     */
    virtual bool update();

    virtual voertuigType getVoertuigType() const;
protected:
    void newSnelheid();
    bool newPositie();
    void newVersnelling();
    virtual bool needVertraging(Voertuig* voorganger);
    virtual bool needStop(Voertuig* voorganger);
};


#endif //RINGSTIMULATOR_VOERTUIG_H
