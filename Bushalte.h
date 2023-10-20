//
// Created by stan on 21/04/22.
//

#ifndef RING_BUSHALTE_H
#define RING_BUSHALTE_H

#include "VerkeersElement.h"

class Bushalte: public VerkeersElement {
private:
    int fWachttijd;
public:
    Bushalte();


    Bushalte(Baan *Baan, double Positie, int Wachttijd);

    /*
     * REQUIRE(this->properlyInitialised(),"Bushalte wasn't initialised when calling getWachttijd");
     */
    int getWachttijd() const;

    /*
     * REQUIRE(this->properlyInitialised(),"Bushalte wasn't initialised when calling setWachttijd");
     * ENSURE(fWachttijd==wachttijd,"setWachttijd postcondition failure");
     */
    void setWachttijd(int Wachttijd);

    virtual void setBaan(Baan *baan);
};


#endif //RING_BUSHALTE_H
