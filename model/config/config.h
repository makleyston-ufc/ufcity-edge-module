//
// Created by makleyston on 02/05/23.
//

#ifndef UFCITY_CONFIG_H
#define UFCITY_CONFIG_H

#include "data_grouping_config.h"
#include "data_aggregation_config.h"

namespace ufcity {

    class config {
    private:
        ufcity::data_grouping_config * dg_config;
        ufcity::data_aggregation_config * da_config;
        ufcity::missing_data_config * md_config;
        ufcity::remove_outliers_config * ro_config;
    public:
        explicit config();
        void set_data_aggregation_config(ufcity::data_aggregation_config * _da_config);
        void set_missing_data_config(ufcity::missing_data_config * _md_config);
        void set_remove_outliers_config(ufcity::remove_outliers_config * _ro_config);
        void set_data_grouping_config(ufcity::data_grouping_config * _dg_config);
        ufcity::data_grouping_config * get_data_grouping_config();
        ufcity::data_aggregation_config * get_data_aggregation_config();
        ufcity::missing_data_config * get_missing_data_config();
        ufcity::remove_outliers_config * get_remove_outliers_config();
    };

} // ufcity

#endif //UFCITY_CONFIG_H
