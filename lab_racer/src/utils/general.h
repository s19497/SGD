//
// Created by Jan Pieczul on 19/05/2021.
//

#ifndef LAB_RACER_GENERAL_H
#define LAB_RACER_GENERAL_H

#include <fstream>

namespace jp_ns {
    bool fileExists(const std::string& path) {
        std::ifstream infile;
        infile.open(path);
        bool result = infile.good();
        infile.close();
        return result;
    }
}

#endif //LAB_RACER_GENERAL_H
