//
// Created by makleyston on 02/05/23.
//

#ifndef UFCITY_SERVICE_H
#define UFCITY_SERVICE_H

#include <vector>
#include <string>
#include "service_data.h"

namespace ufcity {

    class service {
    private:
        std::vector<ufcity::service_data *> data;
        std::string uuid_service;
    public:
        explicit service(std::string _uuid_service);
        std::string get_uuid_service() const;
        void set_data(std::vector<ufcity::service_data *> _data);
        void add_data(ufcity::service_data * _data);
        std::vector<ufcity::service_data *> get_data();
        ufcity::service_data * get_data_by_tag(std::string _tag);
    };

} // ufcity

#endif //UFCITY_SERVICE_H
