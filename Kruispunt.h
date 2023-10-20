//
// Created by dante on 21/04/2022.
//

#ifndef RING_KRUISPUNT_H
#define RING_KRUISPUNT_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Baan;
class Verkeerslicht;
class Kruispunt {
private:
    Kruispunt* fInitCheck;
    pair<Baan*, Baan*> fBanen;
    pair<double, double> fPositie;
    pair<Verkeerslicht*,Verkeerslicht*> fVerkeerslichten;
public:
    bool properlyInitialised() const;
    Kruispunt();
    /*
     * REQUIRE(banen.first!=banen.second,"Kruispunt moet twee verschillende banen hebben");
     * REQUIRE(positie.first>=0 and positie.second>=0,"Posities moeten positief zijn");
     */
    Kruispunt(const pair<Baan*, Baan*> &banen, const pair<double, double> &positie);
    /*
     * REQUIRE(this->properlyInitialised(),"Kruispunt wasn't initialised when calling destructor");
     */
    virtual ~Kruispunt();
    /*
     * REQUIRE(this->properlyInitialised(),"Kruispunt wasn't initialised when calling getBanen");
     */
    const pair<Baan*, Baan*> &getBanen() const;
    /*
     * REQUIRE(this->properlyInitialised(),"Kruispunt wasn't initialised when calling setBanen");
     * REQUIRE(banen.first!=banen.second,"Kruispunt moet twee verschillende banen hebben");
     * REQUIRE(positie.first>=0 and positie.second>=0,"Posities moeten positief zijn");
     * ENSURE(fBanen==banen,"setBanen postcondition failure");
     * ENSURE(fPositie==positie, "setBanen postcondition failure");
     */
    void setBanen(const pair<Baan*, Baan*> &banen, const pair<double, double> &positie);
    /*
     * REQUIRE(this->properlyInitialised(),"Kruispunt wasn't initialised when calling getPositie");
     * REQUIRE(fBanen.first == baan || fBanen.second == baan, "Deze baan behoort niet tot dit kruispunt");
     */
    double getPositie(const Baan* baan) const;
    /*
     * REQUIRE(this->properlyInitialised(),"Kruispunt wasn't initialised when calling getOtherBaan");
     * REQUIRE(fBanen.first == baan || fBanen.second == baan, "Deze baan behoort niet tot dit kruispunt");
     */
    Baan* getOtherBaan(const Baan* baan) const;

    /*
     * REQUIRE(this->properlyInitialised(),"Kruispunt wasn't initialised when calling getVerkeerslichten");
     */
    const pair<Verkeerslicht *, Verkeerslicht *> &getVerkeerslichten() const;

    /*
     * REQUIRE(this->properlyInitialised(),"Kruispunt wasn't initialised when calling setVerkeerslichten");
     * REQUIRE(verkeerslichten.first!=verkeerslichten.second,"Verkeerslichten van kruispunt moeten verschillend zijn");
     * ENSURE(fVerkeerslichten==verkeerslichten,"setVerkeerslichten postcondition failure");
     */
    void setVerkeerslichten(const pair<Verkeerslicht *, Verkeerslicht *> &verkeerslichten);

    /*
     * REQUIRE(this->properlyInitialised(),"Kruispunt wasn't initialised when calling getOtherVerkeerslicht");
     * REQUIRE(fVerkeerslichten.first!=NULL and fVerkeerslichten.second!=NULL,"Er zijn geen verkeerslichten op dit kruispunt");
     */
    Verkeerslicht* getOtherVerkeerslicht(Verkeerslicht* verkeerslicht) const;
};


#endif //RING_KRUISPUNT_H
