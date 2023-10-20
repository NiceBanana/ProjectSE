//
// Created by stan on 23/03/22.
//

#include <gtest/gtest.h>
#include "../Voertuig.h"
#include "../Baan.h"
#include "../VoertuigGenerator.h"

class VoertuigGeneratorTest: public ::testing::Test {
protected:
    friend class VoertuigGenerator;
    VoertuigGenerator* fGenerator;
    Baan* fBaan;
    void SetUp() {
        fBaan = new Baan("Middelheimlaan", 500);
        fGenerator = new VoertuigGenerator(fBaan, 50);
    }
    void TearDown() {
        delete fGenerator;
        delete fBaan;
    }
};

TEST_F(VoertuigGeneratorTest, Contracten) {
    EXPECT_TRUE(fGenerator->properlyInitialised());
    EXPECT_DEATH(VoertuigGenerator(fBaan, 0), "Frequentie moet strikt positief zijn");
    EXPECT_DEATH(fGenerator->setFrequentie(0), "Frequentie moet strikt positief zijn");
    fGenerator->update(60);
    EXPECT_DEATH(fGenerator->update(5), "Tijd is niet vooruitgegaan");
}

TEST_F(VoertuigGeneratorTest, HappyDay) {
    EXPECT_EQ(fGenerator->getBaan(), fBaan);
    EXPECT_EQ(fGenerator->getFrequentie(), 50);
    fGenerator->update(60);
    EXPECT_EQ(fBaan->getVoertuigen().size(), 1);
    fGenerator->update(100);
    EXPECT_EQ(fBaan->getVoertuigen()[0]->getPositie(), 0);
}