//
// Created by stan on 23/03/22.
//
#include <iostream>
#include "utils.h"
#include <gtest/gtest.h>
#include "../VerkeersSituatie.h"

class VerkeersSituatieTest: public ::testing::Test {
protected:
    friend class VerkeersSituatie;
    VerkeersSituatie* fSituatie;
    void SetUp() {
        fSituatie = new VerkeersSituatie();
    }
    void TearDown() {
        delete fSituatie;
    }
};

TEST_F(VerkeersSituatieTest, Contracten) {
    EXPECT_TRUE(fSituatie->properlyInitialised());
}

TEST_F(VerkeersSituatieTest, HappyDaySituatie) {
    fSituatie->fromXML("../../test/HappyDaySituatie.xml");
    ofstream file("../../test/testOut.txt");
    for (int i = 0; i < 5; ++i) {
        fSituatie->print(file);
        for (int j = 0; j < 1000; ++j) {
            fSituatie->nextTijd();
        }
    }
    file.close();
    EXPECT_TRUE(utils::FileCompare("../../test/testOut.txt", "../../test/HappyDaySituatiePrint.txt"));
    fSituatie->fromXML("../../test/HappyDaySituatie.xml");
    file.open("../../test/testOut.txt");
    for (int i = 0; i < 5; ++i) {
        fSituatie->printImpressie(file);
        for (int j = 0; j < 1000; ++j) {
            fSituatie->nextTijd();
        }
    }
    file.close();
    EXPECT_TRUE(utils::FileCompare("../../test/testOut.txt", "../../test/HappyDaySituatiePrintImpressie.txt"));
}

TEST_F(VerkeersSituatieTest, HappyDayBus) {
    fSituatie->fromXML("../../test/HappyDayBus.xml");
    ofstream file("../../test/testOut.txt");
    for (int i = 0; i < 5; ++i) {
        fSituatie->print(file);
        for (int j = 0; j < 750; ++j) {
            fSituatie->nextTijd();
        }
    }
    file.close();
    EXPECT_TRUE(utils::FileCompare("../../test/testOut.txt", "../../test/HappyDayBusPrint.txt"));
    fSituatie->fromXML("../../test/HappyDayBus.xml");
    file.open("../../test/testOut.txt");
    for (int i = 0; i < 5; ++i) {
        fSituatie->printImpressie(file);
        for (int j = 0; j < 750; ++j) {
            fSituatie->nextTijd();
        }
    }
    file.close();
    EXPECT_TRUE(utils::FileCompare("../../test/testOut.txt", "../../test/HappyDayBusPrintImpressie.txt"));
}

TEST_F(VerkeersSituatieTest, HappyDayKruispunt) {
    fSituatie->fromXML("../../test/HappyDayKruispunt.xml");
    ofstream file("../../test/testOut.txt");
    for (int i = 0; i < 10; ++i) {
        fSituatie->print(file);
        for (int j = 0; j < 500; ++j) {
            fSituatie->nextTijd();
        }
    }
    file.close();
    EXPECT_TRUE(utils::FileCompare("../../test/testOut.txt", "../../test/HappyDayKruispuntPrint.txt"));
    fSituatie->fromXML("../../test/HappyDayKruispunt.xml");
    file.open("../../test/testOut.txt");
    for (int i = 0; i < 10; ++i) {
        fSituatie->printImpressie(file);
        for (int j = 0; j < 500; ++j) {
            fSituatie->nextTijd();
        }
    }
    file.close();
    EXPECT_TRUE(utils::FileCompare("../../test/testOut.txt", "../../test/HappyDayKruispuntPrintImpressie.txt"));
}

TEST_F(VerkeersSituatieTest, HappyDayPrioriteit) {
    fSituatie->fromXML("../../test/HappyDayPrioriteit.xml");
    ofstream file("../../test/testOut.txt");
    for (int i = 0; i < 7; ++i) {
        fSituatie->print(file);
        for (int j = 0; j < 750; ++j) {
            fSituatie->nextTijd();
        }
    }
    file.close();
    EXPECT_TRUE(utils::FileCompare("../../test/testOut.txt", "../../test/HappyDayPrioriteitPrint.txt"));
    fSituatie->fromXML("../../test/HappyDayPrioriteit.xml");
    file.open("../../test/testOut.txt");
    for (int i = 0; i < 7; ++i) {
        fSituatie->printImpressie(file);
        for (int j = 0; j < 750; ++j) {
            fSituatie->nextTijd();
        }
    }
    file.close();
    EXPECT_TRUE(utils::FileCompare("../../test/testOut.txt", "../../test/HappyDayPrioriteitPrintImpressie.txt"));
}

TEST_F(VerkeersSituatieTest, Error) {
    testing::internal::CaptureStderr();
    fSituatie->fromXML("../../test/ErrorSituatie1.xml");
    ofstream file("../../test/testOut.txt");
    file << testing::internal::GetCapturedStderr();
    file.close();
    EXPECT_TRUE(utils::FileCompare("../../test/testOut.txt", "../../test/ErrorSituatie1.txt"));
    testing::internal::CaptureStderr();
    fSituatie->fromXML("../../test/ErrorSituatie2.xml");
    file.open("../../test/testOut.txt");
    file << testing::internal::GetCapturedStderr();
    file.close();
    EXPECT_TRUE(utils::FileCompare("../../test/testOut.txt", "../../test/ErrorSituatie2.txt"));
}