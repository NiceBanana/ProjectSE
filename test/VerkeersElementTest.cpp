//
// Created by stan on 4/05/22.
//

#include <gtest/gtest.h>
#include "../VerkeersElement.h"
#include "../Baan.h"

class VerkeersElementTest: public ::testing::Test {
protected:
    friend class Voertuig;
    VerkeersElement* fElement;
    Baan* fBaan;
    void SetUp() {
        fBaan = new Baan("Middelheimlaan", 500);
        fElement = new VerkeersElement(fBaan, 50);
    }
    void TearDown() {
        delete fBaan;
    }
};

TEST_F(VerkeersElementTest, Contracten) {
    EXPECT_TRUE(fElement->properlyInitialised());
    //Constructor
    EXPECT_DEATH(VerkeersElement(fBaan, -5), "Positie moet altijd positief zijn");
    EXPECT_DEATH(VerkeersElement(fBaan, 600), "De positie van het element moet kleiner zijn dan de lengte van de baan");
    //Setup
    Baan *LangeBaan = new Baan("Straat", 5);
    //Setters
    EXPECT_DEATH(fElement->setBaan(LangeBaan), "Lengte van de baan moet groter zijn dan positie VerkeersElement");
    EXPECT_DEATH(fElement->setPositie(-5), "Positie moet altijd positief zijn");
    EXPECT_DEATH(fElement->setPositie(550), "De positie van een VerkeersElement moet kleiner zijn dan de lengte van de baan");
    //Teardown
    delete LangeBaan;
}