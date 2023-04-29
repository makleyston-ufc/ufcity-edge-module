//
// Created by makleyston on 28/04/23.
//

#ifndef UFCITY_DATA_AGGREGATION_CONFIG_H
#define UFCITY_DATA_AGGREGATION_CONFIG_H

#include <string>
#include "missing_data_config.h"
#include "remove_outliers_config.h"

namespace ufcity {

    class data_aggregation_config {
    private:
        long time;
        long size;
        char method;
        missing_data_config * ms_config;
        remove_outliers_config * ro_config;
    public:
        data_aggregation_config();
        void set_method(char _method);
        void set_missing_data_config(missing_data_config * _ms_config);
        void set_remove_outliers_config(remove_outliers_config * _ms_config);
        missing_data_config * get_missing_data_config();
        remove_outliers_config * get_remove_outliers_config();
        void set_size(int _size);
        void set_time(int _sec);
        std::string get_method_str();
        char get_method_char();
    };

}

#endif //UFCITY_DATA_AGGREGATION_CONFIG_H
