//
// Created by stan on 21/03/22.
//

#include "SituatieExceptions.h"
#include <iostream>

string SituatieExceptions::formatKlasse(string message, const string &klasse) {
    std::size_t found = message.find('%');
    if (found != std::string::npos) {
        switch (message[found+1]) {
            case 'k':
                message.replace(found, 2, klasse);
                break;
        }
    }
    return message;
}

string SituatieExceptions::checkString(TiXmlElement *element) {
    if (not element) throw UnknownElementException("Element niet gevonden in %k.");
    try {
        return element->GetText();
    } catch (std::logic_error&) {
        throw InvalidInfoException(string(element->Value()) + " van de %k is niet geldig.");
    }
}

Baan* SituatieExceptions::checkBaan(TiXmlElement* element, map<string, Baan*> searchBaan) {
    string baanNaam = SituatieExceptions::checkString(element);
    if (searchBaan.find(baanNaam) == searchBaan.end())
        throw InconsistantSituationException(baanNaam + " bestaat niet.");
    return searchBaan[baanNaam];
}

int SituatieExceptions::checkStringToInt(TiXmlElement *element) {
    int i;
    if (not element) throw UnknownElementException("Element niet gevonden in %k.");
    try {
        i = atoi(element->GetText());
    } catch (std::invalid_argument&) {
        throw InvalidInfoException(string(element->Value()) + " van de %k is niet geldig.");
    }
    if (i < 0) throw InvalidInfoException(string(element->Value()) + " van het %k is niet geldig.");
    return i;
}

int SituatieExceptions::checkStringToIntAttribute(TiXmlElement *element, const char *name) {
    int i;
    if (not element) throw UnknownElementException("Element niet gevonden in %k.");
    try {
        i = atoi(element->Attribute(name));
    } catch (std::invalid_argument&) {
        throw InvalidInfoException(string(element->Value()) + " van de %k is niet geldig.");
    }
    if (i < 0) throw InvalidInfoException(string(element->Value()) + " van het %k is niet geldig.");
    return i;
}
