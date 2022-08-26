//
// Created by makleyston on 26/08/22.
//

#include "processing.h"

namespace proc {

    int handler(std::string semantic){
        int r = 0;
        r = data_filter(semantic);
        if (r != 0) return r;
        r = data_grouping(semantic);
        if (r != 0) return r;
        return r;
    }

    int data_filter(std::string semantic){
        return 0;
    }

    int data_grouping(std::string semantic){
        return 0;
    }

} // proc