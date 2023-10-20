//
// Created by stan on 23/03/22.
//

#ifndef RING_UTILS_H
#define RING_UTILS_H

#include <iostream>
#include <fstream>
#include <sys/stat.h>
using namespace std;

class utils {
public:
    static bool FileCompare(const std::string leftFileName, const std::string rightFileName);
};


#endif //RING_UTILS_H
