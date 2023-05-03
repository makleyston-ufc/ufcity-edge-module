//
// Created by makleyston on 28/04/23.
//

#ifndef UFCITY_DATA_GROUPING_CONFIG_H
#define UFCITY_DATA_GROUPING_CONFIG_H

#include <string>
#include "missing_data_config.h"
#include "remove_outliers_config.h"
#include "data_aggregation_config.h"

namespace ufcity {

    class data_grouping_config {
    private:
        long time;
        long size;
        char method;
    public:
        explicit data_grouping_config();
        void set_method(char _method);
        void set_size(int _size);
        void set_time(int _sec);
        long get_size() const;
        long get_time() const;
        std::string get_method_str() const;
        char get_method_char() const;
    };

}

#endif //UFCITY_DATA_GROUPING_CONFIG_H
