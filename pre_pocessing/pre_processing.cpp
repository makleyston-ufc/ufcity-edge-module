//
// Created by makleyston on 26/08/22.
//

#include "pre_processing.h"
namespace pre_proc {
    int handler(const ufcity::resource * _resource) {
        int r;
        r = remove_outliers(_resource);
        if (r != 0) return r;
        r = missing_data_insertion(_resource);
        if (r != 0) return r;
        return r;
    }

    int remove_outliers(const ufcity::resource * _resource) {
        return 0;
    }

    int missing_data_insertion(const ufcity::resource * _resource) {
        return 0;
    }
}