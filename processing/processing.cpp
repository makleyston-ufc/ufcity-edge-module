//
// Created by makleyston on 26/08/22.
//

#include "processing.h"

namespace proc {

    int handler(const ufcity::resource * _resource){
        int r;
        r = data_filter(_resource);
        if (r != 0) return r;
        r = data_grouping(_resource);
        if (r != 0) return r;
        return r;
    }

    int data_filter(const ufcity::resource * _resource){
        return 0;
    }

    int data_grouping(const ufcity::resource * _resource){
        return 0;
    }

} // proc