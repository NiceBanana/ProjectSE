//
// Created by dante on 10/05/2022.
//

#ifndef RING_PRIORITEITSVOERTUIG_H
#define RING_PRIORITEITSVOERTUIG_H

#include "Voertuig.h"

class Prioriteitsvoertuig: public Voertuig {
private:
    voertuigType fVoertuigType;
    void setupVariable(voertuigType type);
public:
    Prioriteitsvoertuig(voertuigType Voertuig);

    Prioriteitsvoertuig(Baan *fBaan, int fPositie, double fSnelheid, double fVersnelling, voertuigType fVoertuig);

    virtual voertuigType getVoertuigType() const;

protected:
    bool needVertraging(Voertuig* voorganger);
    bool needStop(Voertuig* voorganger);
};


#endif //RING_PRIORITEITSVOERTUIG_H
