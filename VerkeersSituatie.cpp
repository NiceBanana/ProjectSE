//
// Created by student on 03.03.22.
//

#include <map>
#include <fstream>
#include "lib/tinyxml/tinyxml.h"
#include "VerkeersSituatie.h"
#include "Baan.h"
#include "Verkeerslicht.h"
#include "Voertuig.h"
#include "Bus.h"
#include "Prioriteitsvoertuig.h"
#include "VoertuigGenerator.h"
#include "Bushalte.h"
#include "Kruispunt.h"
#include "SituatieExceptions.h"
#include "lib/DesignByContract.h"

using namespace std;

#define epsilon 0.00000000001

bool VerkeersSituatie::properlyInitialised() const {
    return fInitCheck==this;
}

VerkeersSituatie::VerkeersSituatie() : fTijd(0) {
    fInitCheck=this;
    ENSURE(properlyInitialised(), "constructor must end in properlyInitialised state");
}

VerkeersSituatie::~VerkeersSituatie() {
    REQUIRE(this->properlyInitialised(),"VerkeersSituatie wasn't initialised when calling destructor");
    for (long unsigned int i = 0; i < fBanen.size(); i++) {
        delete fBanen[i];
    }
}

void VerkeersSituatie::pushBackBaan(Baan *baan) {
    REQUIRE(this->properlyInitialised(),"VerkeersSituatie wasn't initialised when calling pushBackBaan");
    fBanen.push_back(baan);
}

const vector<Baan *> &VerkeersSituatie::getBanen() const {
    REQUIRE(this->properlyInitialised(),"VerkeersSituatie wasn't initialised when calling getBanen");
    return fBanen;
}

void VerkeersSituatie::update() {
    REQUIRE(this->properlyInitialised(),"VerkeersSituatie wasn't initialised when calling update");
    REQUIRE(fTijd>=0,"Tijd moet positief zijn ");
    for (long unsigned int i = 0; i < fBanen.size(); i++) {
        vector<Verkeerslicht*> lichten = fBanen[i]->getVerkeerslichten();
        for (long unsigned int j = 0; j < lichten.size(); j++) {
            lichten[j]->update(fTijd);
        }
        vector<Voertuig*> voertuigen = fBanen[i]->getVoertuigen();
        for (long unsigned int j = voertuigen.size() - 1; j < voertuigen.size(); j--) {
            if (not voertuigen[j]->update()) {
                delete voertuigen[j];
                ENSURE( not fBanen[i]->vectorChecker(voertuigen[j]),"Voertuig is niet uit vector verwijderd");
            }
        }
        vector<VoertuigGenerator*> generatoren = fBanen[i]->getVoertuigGeneratoren();
        for(long unsigned int j = 0; j < generatoren.size(); j++) {
            generatoren[j]->update(fTijd);
        }
    }
}

void VerkeersSituatie::print(ostream& stream) const{
    REQUIRE(this->properlyInitialised(),"VerkeersSituatie wasn't initialised when calling print");
    REQUIRE(fTijd>=0,"Tijd moet positief zijn");
    int count=0;
    stream <<"Tijd: "<< fTijd <<endl;
    for(long unsigned int i = 0; i < fBanen.size(); i++){
        vector<Voertuig*> voertuigen = fBanen[i]->getVoertuigen();
        for (long unsigned int j = 0; j < voertuigen.size(); j++) {
            stream <<"Voertuig "<<count<<endl;
            stream <<"-> baan: "<<voertuigen[j]->getBaan()->getNaam()<<endl;
            if (voertuigen[j]->getPositie()<epsilon) {
                stream <<"-> positie: 0"<<endl;
            } else {
                stream <<"-> positie: "<<voertuigen[j]->getPositie()<<endl;
            }
            if (voertuigen[j]->getSnelheid()<epsilon) {
                stream <<"-> snelheid: 0"<<endl;
            } else {
                stream <<"-> snelheid: "<<voertuigen[j]->getSnelheid()<<endl;
            }
            count++;
        }
    }
}

string toLower(string str) {
    for (int i = 0; i < int(str.size()); ++i) {
        str[i] = tolower(str[i]);
    }
    return str;
}

void VerkeersSituatie::fromXML(const char *file) {
    TiXmlDocument doc;
    if(!doc.LoadFile(file)){
        std::cerr<<doc.ErrorDesc()<<std::endl;
        return;
    }
    for (long unsigned int i = 0; i < fBanen.size(); i++) {
        delete fBanen[i];
    }
    fBanen.clear();
    this->fTijd = 0;
    map<string, Baan*> searchBaan;
    for(TiXmlElement* cdelem = doc.FirstChildElement(); cdelem != NULL; cdelem = cdelem->NextSiblingElement()) {
        if (toLower(cdelem->Value()) == "baan") {
            if (string(cdelem->Value()) != "BAAN")
                std::cerr << cdelem->Value() << " moet met hoofdletters maar wordt toch geparst." << std::endl;
            Baan* baan = new Baan();
            try {
                TiXmlElement* element = cdelem->FirstChildElement("naam");
                baan->setNaam(SituatieExceptions::checkString(element));
                element = cdelem->FirstChildElement("lengte");
                baan->setLengte(SituatieExceptions::checkStringToInt(element));
                this->pushBackBaan(baan);
                searchBaan[baan->getNaam()] = baan;
            }
            catch (SituatieExceptions &e) {
                std::cerr << e.what("BAAN") << std::endl;
                delete baan;
            }
        } else if (toLower(cdelem->Value()) == "verkeerslicht") {
            if (string(cdelem->Value()) != "VERKEERSLICHT")
                std::cerr << cdelem->Value() << " moet met hoofdletters maar wordt toch geparst." << std::endl;
            Verkeerslicht* licht = new Verkeerslicht();
            try {
                TiXmlElement* element = cdelem->FirstChildElement("baan");
                licht->setBaan(SituatieExceptions::checkBaan(element, searchBaan));
                element = cdelem->FirstChildElement("positie");
                licht->setPositie(SituatieExceptions::checkStringToInt(element));
                element = cdelem->FirstChildElement("cyclus");
                licht->setCyclus(SituatieExceptions::checkStringToInt(element));
            }
            catch (SituatieExceptions &e) {
                std::cerr << e.what("VERKEERSLICHT") << std::endl;
                delete licht;
            }
        } else if (toLower(cdelem->Value()) == "voertuig") {
            if (string(cdelem->Value()) != "VOERTUIG")
                std::cerr << cdelem->Value() << " moet met hoofdletters maar wordt toch geparst." << std::endl;
            Voertuig* voertuig = NULL;
            try {
                TiXmlElement* element = cdelem->FirstChildElement("type");
                string type = SituatieExceptions::checkString(element);
                if (type == "auto")
                    voertuig = new Voertuig();
                else if (type == "bus")
                    voertuig = new Bus();
                else if (type == "brandweerwagen")
                    voertuig = new Prioriteitsvoertuig(Brandweerwagen);
                else if (type == "ziekenwagen")
                    voertuig = new Prioriteitsvoertuig(Ziekenwagen);
                else if (type == "politiecombi")
                    voertuig = new Prioriteitsvoertuig(Politiecombi);
                else
                    throw InvalidInfoException(string(element->Value()) + " van de %k is niet geldig.");
                element = cdelem->FirstChildElement("baan");
                voertuig->setBaan(SituatieExceptions::checkBaan(element, searchBaan));
                element = cdelem->FirstChildElement("positie");
                voertuig->setPositie(SituatieExceptions::checkStringToInt(element));
            }
            catch (SituatieExceptions &e) {
                std::cerr << e.what("VOERTUIG") << std::endl;
                delete voertuig;
            }
        } else if (toLower(cdelem->Value()) == "voertuiggenerator") {
            if (string(cdelem->Value()) != "VOERTUIGGENERATOR")
                std::cerr << cdelem->Value() << " moet met hoofdletters maar wordt toch geparst." << std::endl;
            VoertuigGenerator* voertuigGenerator = new VoertuigGenerator();
            try {
                TiXmlElement* element = cdelem->FirstChildElement("baan");
                voertuigGenerator->setBaan(SituatieExceptions::checkBaan(element, searchBaan));
                element = cdelem->FirstChildElement("frequentie");
                voertuigGenerator->setFrequentie(SituatieExceptions::checkStringToInt(element));
            }
            catch (SituatieExceptions &e) {
                std::cerr << e.what("VOERTUIGGENERATOR") << std::endl;
                delete voertuigGenerator;
            }
        } else if (toLower(cdelem->Value()) == "bushalte") {
            if (string(cdelem->Value()) != "BUSHALTE")
                std::cerr << cdelem->Value() << " moet met hoofdletters maar wordt toch geparst." << std::endl;
            Bushalte *bushalte = new Bushalte();
            try {
                TiXmlElement *element = cdelem->FirstChildElement("baan");
                bushalte->setBaan(SituatieExceptions::checkBaan(element, searchBaan));
                element = cdelem->FirstChildElement("positie");
                bushalte->setPositie(SituatieExceptions::checkStringToInt(element));
                element = cdelem->FirstChildElement("wachttijd");
                bushalte->setWachttijd(SituatieExceptions::checkStringToInt(element));
            }
            catch (SituatieExceptions &e) {
                std::cerr << e.what("BUSHALTE") << std::endl;
                delete bushalte;
            }
        } else if (toLower(cdelem->Value()) == "kruispunt") {
            if (string(cdelem->Value()) != "KRUISPUNT")
                std::cerr << cdelem->Value() << " moet met hoofdletters maar wordt toch geparst." << std::endl;
            Kruispunt *kruispunt = new Kruispunt();
            try {
                pair<Baan*, Baan*> banen;
                pair<double, double> positie;
                TiXmlElement *element = cdelem->FirstChildElement("baan");
                banen.first = SituatieExceptions::checkBaan(element, searchBaan);
                positie.first = double(SituatieExceptions::checkStringToIntAttribute(element, "positie"));
                element = element->NextSiblingElement();
                banen.second = SituatieExceptions::checkBaan(element, searchBaan);
                positie.second = double(SituatieExceptions::checkStringToIntAttribute(element, "positie"));
                kruispunt->setBanen(banen, positie);
                pair<Verkeerslicht*, Verkeerslicht*> lichten;
                vector<Verkeerslicht*> verkeerslichten = banen.first->getVerkeerslichten();
                for (long unsigned int i = 0; i < verkeerslichten.size(); ++i) {
                    if (positie.first == verkeerslichten[i]->getPositie()) {
                        lichten.first = verkeerslichten[i];
                        break;
                    }
                }
                verkeerslichten = banen.second->getVerkeerslichten();
                for (long unsigned int i = 0; i < verkeerslichten.size(); ++i) {
                    if (positie.second == verkeerslichten[i]->getPositie()) {
                        lichten.second = verkeerslichten[i];
                        lichten.second->setMaster(false);
                        lichten.second->setKleur(groen);
                        break;
                    }
                }
                kruispunt->setVerkeerslichten(lichten);
            }
            catch (SituatieExceptions &e) {
                std::cerr << e.what("KRUISPUNT") << std::endl;
                delete kruispunt;
            }
        } else {
            std::cerr << cdelem->Value() << " word niet herkent." << std::endl;
        }
    }
    doc.Clear();
}

void VerkeersSituatie::printImpressie(ostream& stream) const {
    for (long unsigned int i = 0; i < fBanen.size(); ++i) {
        string verkeerslichten;
        string bushaltes;
        stream << fBanen[i]->getNaam();
        stream << "\t\t| ";;
        const vector<Voertuig*> voertuigen = fBanen[i]->getVoertuigen();
        const vector<Verkeerslicht*> lichten = fBanen[i]->getVerkeerslichten();
        const vector<Bushalte*> bushalte = fBanen[i]->getBushaltes();
        long unsigned int curVoertuig = 0;
        long unsigned int curLicht = 0;
        long unsigned int curHalte = 0;
        for (int j = 0; j < fBanen[i]->getLengte() / 2; ++j) {
            if (curVoertuig < voertuigen.size() && voertuigen[curVoertuig]->getPositie() / 2 <= j) {
                switch (voertuigen[curVoertuig]->getVoertuigType()) {
                    case Auto:
                        stream << 'a';
                        break;
                    case bus:
                        stream << 'b';
                        break;
                    case Brandweerwagen:
                        stream << 'B';
                        break;
                    case Ziekenwagen:
                        stream << 'Z';
                        break;
                    case Politiecombi:
                        stream << 'P';
                        break;
                }
                curVoertuig++;
            } else
                stream << '=';
            if (curLicht < lichten.size() && lichten[curLicht]->getPositie() / 2 <= j) {
                switch (lichten[curLicht]->getKleur()) {
                    case groen:
                        verkeerslichten += 'G';
                    case rood:
                        verkeerslichten += 'R';
                        break;
                    case oranje:
                        verkeerslichten += 'O';
                        break;
                }
                curLicht++;
            }
            if (curHalte < bushalte.size() && bushalte[curHalte]->getPositie() / 2 <= j) {
                if (verkeerslichten.size() == bushaltes.size()) {
                    verkeerslichten += '|';
                }
                bushaltes += 'B';
                curHalte++;
                continue;
            }
            bushaltes += ' ';
            if (verkeerslichten.size() < bushaltes.size()) {
                verkeerslichten += ' ';
            }
        }
        stream << '\n';
        stream << " > verkeerslichten\t" << verkeerslichten << '\n';
        stream << " > bushaltes\t\t" << bushaltes << '\n';
        stream << '\n';
    }
}

void VerkeersSituatie::nextTijd() {
    REQUIRE(this->properlyInitialised(),"Situatie wasn't initialised when calling nextTijd");
    fTijd += simulatietijd;
    std::cout << fTijd << std::endl;
    update();
    ENSURE(fTijd>0,"Tijd moet strikt postief zijn");
}

void VerkeersSituatie::exportGraphics(ostream &stream) const {
    string banen;
    int aantalfiguren = 0;
    for (long unsigned int i = 0; i < fBanen.size(); ++i) {
        banen += "[Figure" + to_string(aantalfiguren) + "]\n"
                 "type = \"Cube\"\n"
                 "rotateX = 0\n"
                 "rotateY = 0\n"
                 "rotateZ = 0\n"
                 "scaleTuple = (1.0, " + to_string(fBanen[i]->getLengte()) + ", 0.5)\n"
                 "center = (" + to_string(i * 5) + ", " + to_string(fBanen[i]->getLengte()/2) + ", 0)\n"
                 "ambientReflection = (0.25, 0.25, 0.25)\n"
                 "diffuseReflection = (0.25, 0.25, 0.25)\n\n";
        aantalfiguren++;
        vector<Voertuig*> voertuigen = fBanen[i]->getVoertuigen();
        for (long unsigned int j = 0; j < voertuigen.size(); ++j) {
            banen += "[Figure" + to_string(aantalfiguren) + "]\n"
                     "type = \"Cube\"\n"
                     "rotateX = 0\n"
                     "rotateY = 0\n"
                     "rotateZ = 0\n"
                     "scaleTuple = (1.0, " + to_string(voertuigen[j]->getLengte()) + ", 1.0)\n"
                     "center = (" + to_string(double(i * 5) + 0.5) + ", " + to_string(std::max(voertuigen[j]->getPositie() - voertuigen[j]->getLengte()/2.0, 0.0)) + ", 0)\n"
                     "ambientReflection = (0.25, 0.25, 0.25)\n";
            aantalfiguren++;
            switch (voertuigen[j]->getVoertuigType()) {
                case Brandweerwagen:
                    banen += "diffuseReflection = (1.0, 0.0, 0.0)\n";
                    break;
                case Ziekenwagen:
                    banen += "diffuseReflection = (1.0, 1.0, 0.0)\n";
                    break;
                case Politiecombi:
                    banen += "diffuseReflection = (0.0, 0.0, 1.0)\n";
                    break;
                case Auto:
                    banen += "diffuseReflection = (0.0, 1.0, 0.0)\n";
                    break;
                case bus:
                    banen += "diffuseReflection = (1.0, 1.0, 1.0)\n";
                    break;
            }
            banen += '\n';
        }
        vector<Verkeerslicht*> lichten = fBanen[i]->getVerkeerslichten();
        for (long unsigned int j = 0; j < lichten.size(); ++j) {
            banen += "[Figure" + to_string(aantalfiguren) + "]\n"
                     "type = \"Cube\"\n"
                     "rotateX = 0\n"
                     "rotateY = 0\n"
                     "rotateZ = 0\n"
                     "scaleTuple = (1.0, 0.25, 1.0)\n"
                     "center = (" + to_string(double(i * 5) + 0.5) + ", " + to_string(lichten[j]->getPositie()) + ", 0)\n"
                     "ambientReflection = (0.25, 0.25, 0.25)\n";
            aantalfiguren++;
            switch (lichten[j]->getKleur()) {
                case groen:
                    banen += "diffuseReflection = (0.0, 1.0, 0.0)\n";
                    break;
                case rood:
                    banen += "diffuseReflection = (1.0, 0.0, 0.0)\n";
                    break;
                case oranje:
                    banen += "diffuseReflection = (1.0, 0.5, 0.0)\n";
                    break;
            }
            banen += '\n';
        }

    }
    stream << "[General]\n"
              "type = \"LightedZBuffering\"\n"
              "nrLights = 1\n"
              "size = 2000\n"
              "backgroundcolor = (0, 0, 0)\n"
              "nrFigures = " + to_string(aantalfiguren) + "\n"
              "eye = (0, 0, 150)\n"
              "\n"
              "[Light0]\n"
              "infinity = TRUE\n"
              "direction = (-1, 1, -1)\n"
              "ambientLight = (1, 1, 1)\n"
              "diffuseLight = (1, 1, 1)\n\n";

    stream << banen;
}
