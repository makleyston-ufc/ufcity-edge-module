//
// Created by makleyston on 23/08/22.
//

#ifndef UFCITY_LOCATION_MODEL_H
#define UFCITY_LOCATION_MODEL_H

#include <string>

namespace ufcity {

    class location_model {
    private:
        std::string lat;
        std::string lng;

    public:
//        location_model(std::string lat, std::string lng):lat(lat), lng(lng){};
//        location_model();

        std::string get_lat();
        std::string get_lng();
        void set_lat(std::string lat);
        void set_lng(std::string lng);
    };

} // ufcity


#endif //UFCITY_LOCATION_MODEL_H
