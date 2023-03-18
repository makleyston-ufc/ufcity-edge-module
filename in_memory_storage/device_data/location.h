//
// Created by makleyston on 17/03/23.
//

#ifndef UFCITY_LOCATION_H
#define UFCITY_LOCATION_H

#include <string>

namespace ufcity {

    class location {
    private:
        std::string lat;
        std::string lng;
        std::string alt;

    public:
        std::string get_lat();
        std::string get_lng();
        std::string get_alt();

        void set_lat(const std::string& _lat);
        void set_lng(const std::string& _lng);
        void set_alt(const std::string& _alt);
    };

} // ufcity

#endif //UFCITY_LOCATION_H
