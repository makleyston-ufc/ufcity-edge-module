//
// Created by makleyston on 26/08/22.
//

#include "processing.h"

namespace proc {

    int handler(const std::string& semantic){
        int r;
        r = data_filter(semantic);
        if (r != 0) return r;
        r = data_grouping(semantic);
        if (r != 0) return r;
        return r;
    }

    int data_filter(const std::string& semantic){
        return 0;
    }

    int data_grouping(const std::string& semantic){
        return 0;
    }

} // proc