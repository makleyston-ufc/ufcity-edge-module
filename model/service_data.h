//
// Created by makleyston on 02/05/23.
//

#ifndef UFCITY_SERVICE_DATA_H
#define UFCITY_SERVICE_DATA_H

#include <string>

namespace ufcity {

    class service_data {
    private:
        std::string tag;
        std::string value;
    public:
        explicit service_data(std::string _tag, std::string _value);
        std::string get_tag();
        std::string get_value();
    };

} // ufcity

#endif //UFCITY_SERVICE_DATA_H
