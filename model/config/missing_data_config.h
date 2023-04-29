//
// Created by makleyston on 28/04/23.
//

#ifndef UFCITY_MISSING_DATA_CONFIG_H
#define UFCITY_MISSING_DATA_CONFIG_H

#include <string>

namespace ufcity {

    class missing_data_config {
    private:
        char method;
    public:
        missing_data_config();
        explicit missing_data_config(char _method);
        void set_method(char method);
        std::string get_method_str();
        char get_method_char();
    };

} // ufcity

#endif //UFCITY_MISSING_DATA_CONFIG_H
