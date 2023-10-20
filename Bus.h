//
// Created by dante on 9/05/2022.
//

#ifndef RING_BUS_H
#define RING_BUS_H

#include "Voertuig.h"

class Bus: public Voertuig {
private:
    pair<Bushalte*, double> fWacht;
public:
    Bus();

    Bus(Baan *fBaan, int fPositie, double fSnelheid, double fVersnelling);

    bool update();

    virtual voertuigType getVoertuigType() const;

protected:
    bool needVertraging(Voertuig* voorganger);
    bool needStop(Voertuig* voorganger);
};


#endif //RING_BUS_H
