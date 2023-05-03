//
// Created by makleyston on 03/05/23.
//

#ifndef UFCITY_DATA_AGGREGATION_CONFIG_H
#define UFCITY_DATA_AGGREGATION_CONFIG_H

#include "missing_data_config.h"
#include "remove_outliers_config.h"

namespace ufcity {

    class data_aggregation_config {
    private:
        char method;
    public:
        data_aggregation_config();
        explicit data_aggregation_config(char _method);
        void set_method(char _method);
        std::string get_method_str() const;
        char get_method_char() const;
    };

} // ufcity

#endif //UFCITY_DATA_AGGREGATION_CONFIG_H
