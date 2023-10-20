//
// Created by stan on 28/03/22.
//

#ifndef RING_VERKEERSELEMENT_H
#define RING_VERKEERSELEMENT_H

class Baan;

enum elementType {
    VOERTUIG,
    VERKEERSLICHT,
    GENERATOR,
    BUSHALTE
};

class VerkeersElement {
protected:
    VerkeersElement* fInitCheck;
    elementType fType;
    Baan* fBaan;
    double fPositie;
public:
    virtual bool properlyInitialised() const;

    /*
     * ENSURE(properlyInitialised(), "constructor must end in properlyInitialised state");
     */
    VerkeersElement();

    /*
     * REQUIRE(positie>=0,"Positie moet altijd positief zijn");
     * REQUIRE(positie<baan->getLengte(),"De positie van het element moet kleiner zijn dan de lengte van de baan");
     * ENSURE(properlyInitialised(), "constructor must end in properlyInitialised state");
     */
    VerkeersElement(Baan *fBaan, double fPositie);


    virtual ~VerkeersElement();

    /*
     * REQUIRE(this->properlyInitialised(),"VerkeersElement wasn't initialised when calling getBaan");
     */
    virtual Baan *getBaan() const;

    /*
     * REQUIRE(this->properlyInitialised(),"VerkeersElement wasn't initialised when calling setBaan");
     * REQUIRE(this->fPositie<baan->getLengte(),"Lengte van de baan moet groter zijn dan positie VerkeersElement");
     * ENSURE(fBaan==baan,"setBaan postcondition failure");
     */
    virtual void setBaan(Baan *baan);

    /*
     * REQUIRE(this->properlyInitialised(),"VerkeersElement wasn't initialised when calling getPositie");
     * ENSURE(fPositie>=0,"De positie van VerkeersElement is niet positief");
     */
    virtual double getPositie() const;

    /*
     * REQUIRE(this->properlyInitialised(),"VerkeersElement wasn't initialised when calling setPositie");
     * REQUIRE(positie >= 0, "Positie moet altijd positief zijn");
     * REQUIRE(positie<this->getBaan()->getLengte(),"De positie van een VerkeersElement moet kleiner zijn dan de lengte van de baan");
     * ENSURE(fPositie==double(positie),"setPositie postcondition failure");
     */
    virtual void setPositie(int positie);

    /*
     * REQUIRE(this->properlyInitialised(),"VerkeersElement wasn't initialised when calling getType");
     */
    virtual elementType getType() const;
};


#endif //RING_VERKEERSELEMENT_H
