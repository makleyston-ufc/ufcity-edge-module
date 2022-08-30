//
// Created by makleyston on 26/08/22.
//

#ifndef UFCITY_PROCESSING_H
#define UFCITY_PROCESSING_H

#include <string>

namespace proc {

    int handler(const std::string& semantic);
    int data_filter(const std::string& semantic);
    int data_grouping(const std::string& semantic);

} // proc

#endif //UFCITY_PROCESSING_H
