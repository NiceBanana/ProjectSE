//
// Created by stan on 21/03/22.
//

#ifndef RING_SITUATIEEXCEPTIONS_H
#define RING_SITUATIEEXCEPTIONS_H

#include <string>
#include <exception>
#include <map>
#include "lib/tinyxml/tinyxml.h"
#include "Baan.h"

using namespace std;

class SituatieExceptions : public exception {
protected:
    string message;
public:
    static string formatKlasse(string message, const string &klasse);
    static string checkString(TiXmlElement* element);
    static Baan* checkBaan(TiXmlElement* element, map<string, Baan*> searchBaan);
    static int checkStringToInt(TiXmlElement* element);
    static int checkStringToIntAttribute(TiXmlElement* element, const char* name);
    SituatieExceptions(const string &message) : message(message) {}
    virtual ~SituatieExceptions() throw() {}
    virtual const char* what(const string &klasse) {
        message = SituatieExceptions::formatKlasse(message, klasse);
        return message.c_str();
    }
};

struct UnknownElementException: public SituatieExceptions {
    UnknownElementException(const string &message) : SituatieExceptions(message) {}
};

struct InvalidInfoException: public SituatieExceptions {
    InvalidInfoException(const string &message) : SituatieExceptions(message) {}
};

struct InconsistantSituationException: public SituatieExceptions {
    InconsistantSituationException(const string &message) : SituatieExceptions(message) {}
};

#endif //RING_SITUATIEEXCEPTIONS_H
