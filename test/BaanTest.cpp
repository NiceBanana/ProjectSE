//
// Created by stan on 5/03/22.
//

#include <gtest/gtest.h>
#include "../Baan.h"
#include "../Voertuig.h"
#include "../Verkeerslicht.h"

class BaanTest: public ::testing::Test {
protected:
    friend class Baan;
    Baan* fBaan;
    Voertuig *fAuto1, *fAuto2;
    Verkeerslicht *fLicht;
    void SetUp() {
        fBaan = new Baan("Middelheimlaan", 500);
        fAuto1 = new Voertuig(fBaan, 50, 0, 0);
        fAuto2 = new Voertuig(fBaan, 100, 0, 0);
        fLicht = new Verkeerslicht(fBaan, 75, 5);
    }
    void TearDown() {
        delete fAuto1;
        delete fAuto2;
        delete fLicht;
    }
};

TEST_F(BaanTest, Contracten) {
    EXPECT_TRUE(fBaan->properlyInitialised());
    //Constructor
    EXPECT_DEATH(Baan("StalinStraat", -5), "Baan moet een strikt positieve lengte hebben");
    Baan* testBaan = new Baan("StalinStraat", 600);
    //Setup
    Voertuig* voertuig = new Voertuig(testBaan, 550, 0, 0);
    Verkeerslicht* licht = new Verkeerslicht(testBaan, 550, 3);
    //Voertuig
    EXPECT_DEATH(fBaan->addVoertuig(voertuig), "Banen komen niet overeen");
    voertuig->setPositie(50);
    EXPECT_DEATH(voertuig->setBaan(testBaan), "Voertuig zit al in de vector");
    EXPECT_DEATH(fBaan->addVoertuig(voertuig), "Banen komen niet overeen");
    testBaan->deleteElement(voertuig);
    voertuig->setBaan(fBaan);
    EXPECT_DEATH(fBaan->addVoertuig(voertuig), "Voertuig zit al in de vector");
    fBaan->deleteElement(voertuig);
    voertuig->setBaan(testBaan);
    EXPECT_DEATH(fBaan->deleteElement(voertuig), "Banen komen niet overeen");
    testBaan->deleteElement(voertuig);
    //Licht
    EXPECT_DEATH(fBaan->addVerkeerslicht(licht), "Banen komen niet overeen");
    licht->setPositie(50);
    EXPECT_DEATH(licht->setBaan(testBaan), "Verkeerslicht zit al in de vector");
    EXPECT_DEATH(fBaan->addVerkeerslicht(licht), "Banen komen niet overeen");
    testBaan->deleteElement(licht);
    licht->setBaan(fBaan);
    EXPECT_DEATH(fBaan->addVerkeerslicht(licht), "Verkeerslicht zit al in de vector");
    fBaan->deleteElement(licht);
    licht->setBaan(testBaan);
    EXPECT_DEATH(fBaan->deleteElement(licht), "Banen komen niet overeen");
    testBaan->deleteElement(licht);
    //Teardown
    delete voertuig;
    delete testBaan;
    delete licht;
}

TEST_F(BaanTest, HappyDay) {
    EXPECT_EQ(fBaan->getNaam(), "Middelheimlaan");
    EXPECT_EQ(fBaan->getLengte(), 500);
    EXPECT_EQ(fBaan->getVoorganger(fAuto1), fAuto2);
    EXPECT_TRUE(fBaan->getVoorganger(fAuto2) == NULL);
    EXPECT_EQ(fBaan->getVolgganger(fAuto2), fAuto1);
    EXPECT_TRUE(fBaan->getVolgganger(fAuto1) == NULL);
    EXPECT_EQ(fBaan->getVolgendeLicht(fAuto1), fLicht);
    EXPECT_TRUE(fBaan->getVolgendeLicht(fAuto2) == NULL);
}
