//
// Created by makleyston on 02/05/23.
//

#include "config.h"
#include "methods.h"

namespace ufcity {
    config::config() {
        this->da_config = new ufcity::data_aggregation_config();
        this->da_config->set_method(methods::NONE);

        this->dg_config = new ufcity::data_grouping_config();
        this->dg_config->set_method(methods::NONE);

        this->md_config = new ufcity::missing_data_config();
        this->md_config->set_method(methods::NONE);

        this->ro_config = new ufcity::remove_outliers_config();
        this->ro_config->set_method(methods::NONE);
    }

    void config::set_data_grouping_config(ufcity::data_grouping_config *_dg_config) {
        this->dg_config = _dg_config;
    }

    void config::set_missing_data_config(ufcity::missing_data_config *_md_config) {
        this->md_config = _md_config;
    }

    void config::set_remove_outliers_config(ufcity::remove_outliers_config *_ro_config) {
        this->ro_config = _ro_config;
    }

    void config::set_data_aggregation_config(ufcity::data_aggregation_config *_da_config) {
        this->da_config = _da_config;
    }

    ufcity::data_grouping_config *config::get_data_grouping_config() {
        return this->dg_config;
    }

    ufcity::missing_data_config *config::get_missing_data_config() {
        return this->md_config;
    }

    ufcity::remove_outliers_config *config::get_remove_outliers_config() {
        return this->ro_config;
    }

    ufcity::data_aggregation_config *config::get_data_aggregation_config() {
        return this->da_config;
    }

} // ufcity