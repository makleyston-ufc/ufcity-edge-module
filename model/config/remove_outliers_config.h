//
// Created by makleyston on 28/04/23.
//

#ifndef UFCITY_REMOVE_OUTLIERS_CONFIG_H
#define UFCITY_REMOVE_OUTLIERS_CONFIG_H

#include <string>


namespace ufcity {
    class remove_outliers_config {
    private:
        double threshold;
        char method;
        double upper_per;
        double lower_per;

    public:
        remove_outliers_config();
        void set_method(char _method);
        void set_threshold(double _threshold);
        std::string get_method_str();
        char get_method_char();
        double get_threshold();
        double get_upper_percentile();
        double get_lower_percentile();
        void set_lower_percentile(double _lower);
        void set_upper_percentile(double _upper);
    };
}

#endif //UFCITY_REMOVE_OUTLIERS_CONFIG_H
