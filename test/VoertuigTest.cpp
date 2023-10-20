//
// Created by stan on 22/03/22.
//

#include <gtest/gtest.h>
#include "../Voertuig.h"
#include "../Baan.h"

class VoertuigTest: public ::testing::Test {
protected:
    friend class Voertuig;
    Voertuig* fVoertuig;
    Baan* fBaan;
    void SetUp() {
        fBaan = new Baan("Middelheimlaan", 500);
        fVoertuig = new Voertuig();
        fVoertuig->setPositie(5);
        fVoertuig->setBaan(fBaan);
    }
    void TearDown() {
        delete fVoertuig->getBaan();
    }
};

TEST_F(VoertuigTest, Contracten) {
    EXPECT_TRUE(fVoertuig->properlyInitialised());
    //Constructor
    EXPECT_DEATH(Voertuig(NULL, -5, 5, 0), "Positie moet altijd positief zijn");
    EXPECT_DEATH(Voertuig(fBaan, 550, 5, 0), "De positie van het element moet kleiner zijn dan de lengte van de baan");
    EXPECT_DEATH(Voertuig(fBaan, 10, -5, 0), "Snelheid moet altijd positief zijn");
    EXPECT_DEATH(Voertuig(NULL, 10, -5, 0), "Baan moet bestaan");
    // Setters
    EXPECT_DEATH(fVoertuig->setSnelheid(-5), "Snelheid moet altijd positief zijn");
}

TEST_F(VoertuigTest, HappyDayAuto) {
    Baan* baan = fVoertuig->getBaan();
    EXPECT_EQ(baan->getNaam(), fBaan->getNaam());
    EXPECT_EQ(baan->getLengte(), fBaan->getLengte());
    EXPECT_EQ(fVoertuig->getPositie(), 5);
    fVoertuig->setPositie(0);
    fVoertuig->setSnelheid(0);
    fVoertuig->setVersnelling(0);
    fVoertuig->update();
    EXPECT_FLOAT_EQ(fVoertuig->getVersnelling(), 1.44);
    for (int i = 0; i < 100; ++i) {
        fVoertuig->update();
    }
    EXPECT_FLOAT_EQ(fVoertuig->getPositie(), 2.0236542);
    EXPECT_FLOAT_EQ(fVoertuig->getSnelheid(), 2.3901997);
}