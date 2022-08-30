//
// Created by makleyston on 26/08/22.
//

#include "pre_processing.h"
namespace pre_proc {
    int handler(const std::string& semantic) {
        int r;
        r = remove_outliers(semantic);
        if (r != 0) return r;
        r = missing_data_insertion(semantic);
        if (r != 0) return r;
        return r;
    }

    int remove_outliers(const std::string& semantic) {
        return 0;
    }

    int missing_data_insertion(const std::string& semantic) {
        return 0;
    }
}