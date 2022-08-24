//
// Created by makleyston on 12/08/22.
//

#include <iostream>
#include "ufcity_observer.h"

namespace ufcity {
    void ufcity_observer::command_received(std::string) {
        std::cout << "Observer OK!" << std::endl;
    }
} // ufcity