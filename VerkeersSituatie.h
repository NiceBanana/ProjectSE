//
// Created by student on 03.03.22.
//

#ifndef INC_VERKEERSSITUATIE_H
#define INC_VERKEERSSITUATIE_H

#include <iostream>
#include <vector>
#include <string>
#include <exception>

using namespace std;

class Baan;
class Verkeerslicht;
class Voertuig;
class VoertuigGenerator;

class VerkeersSituatie {
private:
    VerkeersSituatie* fInitCheck;
    double fTijd;
    vector<Baan*> fBanen;
public:
    bool properlyInitialised() const;

    /*
     * ENSURE(properlyInitialised(), "constructor must end in properlyInitialised state");
     */
    VerkeersSituatie();

    /*
     * REQUIRE(this->properlyInitialised(),"VerkeersSituatie wasn't initialised when calling destructor");
     */
    virtual ~VerkeersSituatie();

    /*
     * REQUIRE(this->properlyInitialised(),"VerkeersSituatie wasn't initialised when calling pushBackBaan");
     */
    void pushBackBaan(Baan* baan);

    /*
     * REQUIRE(this->properlyInitialised(),"VerkeersSituatie wasn't initialised when calling getBanen");
     */
    const vector<Baan *> &getBanen() const;

    /*
     * REQUIRE(this->properlyInitialised(),"VerkeersSituatie wasn't initialised when calling update");
     * REQUIRE(fTijd>=0,"Tijd moet positief zijn ");
     */
    void update();

    /*
     * REQUIRE(this->properlyInitialised(),"VerkeersSituatie wasn't initialised when calling print");
     * REQUIRE(fTijd>=0,"Tijd moet positief zijn");
     */
    void print(ostream& stream) const;


    void fromXML(const char* file);

    void printImpressie(ostream& stream) const;

    void exportGraphics(ostream& stream) const;

    /*
     * REQUIRE(this->properlyInitialised(),"Situatie wasn't initialised when calling nextTijd");
     * ENSURE(fTijd>0,"Tijd moet strikt postief zijn");
     */
    void nextTijd();
};


#endif //RINGSTIMULATOR_VERKEERSSITUATIE_H
